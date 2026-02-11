jsspiSend8bit(IOEventFlags device, unsigned char data, int bit0, int bit1) {


  jshSPISend(device, ((((data>>7)&1) ? bit1 : bit0)<<8) | (((data>>6)&1) ? bit1 : bit0));
  jshSPISend(device, ((((data>>5)&1) ? bit1 : bit0)<<8) | (((data>>4)&1) ? bit1 : bit0));
  jshSPISend(device, ((((data>>3)&1) ? bit1 : bit0)<<8) | (((data>>2)&1) ? bit1 : bit0));
  jshSPISend(device, ((((data>>1)&1) ? bit1 : bit0)<<8) | (((data>>0)&1) ? bit1 : bit0));
}
