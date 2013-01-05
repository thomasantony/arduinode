/* 
 * Copyright (c) 2011, Jan Clement
 * licenced under the GPL
 *
 * Author: Jan Clement <jan.clement@audiokits.de>
 *
 * This file is part of the arduiNode library
 * http://code.google.com/p/arduinode/
 */

#include "arduiNode.h"
#include "includes.h"
uint8_t NODETYPE;
#include "driver/rfm12/rfm12.h"  // FIXME 

// driver stuff
// static struct pt pt_rcvPkt;

// Global variables for the driver
uint8_t NODE_IR_ACTIVE, PHY_CHANNEL_FREE = true;
volatile unsigned long PHY_CHANNEL_BUSY_TIME;

void arduiNodeSetup(uint8_t NODETYP) {
  NODETYPE = NODETYP;
  IR_INIT_PT_RCV();		// init proto rcv var called in isr
  init_pt_snd();		// init proto snd var...
  #if SERIALCONSOLE
  Serial.print("arduiNode 1.0");
  #endif
  if(NODETYPE == MASTER) {
    myself.id  = 1;
    myself.htm = 0;
    #if SERIALCONSOLE
    Serial.println(" MASTER");
    #endif
  }
  else if(NODETYPE == SLAVE){
    myself.id  = 0;
    myself.htm = 255;
    #if SERIALCONSOLE
    Serial.println(" SLAVE");
    #endif
  }
  else {
      #if SERIALCONSOLE
      Serial.println(" NDF");
      #endif
  }
  
  enable_IR_rx();
  
  pinMode(STATUSLEDPIN, OUTPUT);	// STATUS LED
  
  RXTX_DRIVER_INIT();
  
  //setupScheduler();
  
}

void arduiNodeSetID(unsigned char id) {
	myself.id = id;
}


void statusLED(unsigned char led){
  digitalWrite(STATUSLEDPIN, led);
}
