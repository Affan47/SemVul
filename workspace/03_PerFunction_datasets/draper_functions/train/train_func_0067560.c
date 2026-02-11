dump_atmtext(const AtmAddr_t addr)
{
  int i;
  char buffer[ATM_ADDR_LEN*3+2];

  for (i=0;i<ATM_ADDR_LEN;i++) {
    sprintf(&buffer[i*2], "%2.2x ", 0xff&(unsigned char)addr.addr[i]);
  }
  dump_printf(EL_CONT, "%s", buffer);
}
