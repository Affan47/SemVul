mem_write_0000_1fff_default(Uint16 adr,Uint8 v) {
  if ((v&0x0f)==0x0a) enable_ram();
  else disable_ram();
}
