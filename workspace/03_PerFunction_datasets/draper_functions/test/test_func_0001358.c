exec86(uint8_t aelle, uint8_t cielle, char *curremu, int *retval) {
  int len = 0;
  *retval=0;
  while (len <0x24) {
    uint8_t opcode = curremu[len], support;
    len++;
    switch (opcode) {
      case 0xeb:
        len++;
      case 0x0a:
        len++;
      case 0x90:
      case 0xf8:
      case 0xf9:
        break;

      case 0x02:
        aelle+=cielle;
	len++;
        break;
      case 0x2a:
        aelle-=cielle;
	len++;
        break;
      case 0x04:
        aelle+=curremu[len];
	len++;
        break;
      case 0x2c:
        aelle-=curremu[len];
	len++;
        break;
      case 0x32:
        aelle^=cielle;
	len++;
        break;
      case 0x34:
        aelle^=curremu[len];
	len++;
        break;

      case 0xfe:
        if ( curremu[len] == '\xc0' ) aelle++;
	else aelle--;
        len++;
        break;

      case 0xc0:
	support = curremu[len];
        len++;
        if ( support == 0xc0 ) CLI_ROL(aelle, curremu[len]);
        else CLI_ROR(aelle, curremu[len]);
        len++;
        break;

      default:
        cli_dbgmsg("spin: bogus opcode %x\n", opcode);
	*retval=1;
	return aelle;
    }
  }
  if ( len!=0x24 || curremu[len]!='\xaa' ) {
    cli_dbgmsg("spin: bad emucode\n");
    *retval=1;
  }
  return aelle;
}
