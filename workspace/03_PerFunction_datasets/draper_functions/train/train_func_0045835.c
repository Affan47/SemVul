stk500v2_loadaddr(PROGRAMMER * pgm, unsigned int addr)
{
  unsigned char buf[16];
  int result;

  DEBUG("STK500V2: stk500v2_loadaddr(%d)\n",addr);

  buf[0] = CMD_LOAD_ADDRESS;
  buf[1] = (addr >> 24) & 0xff;
  buf[2] = (addr >> 16) & 0xff;
  buf[3] = (addr >> 8) & 0xff;
  buf[4] = addr & 0xff;

  result = stk500v2_command(pgm, buf, 5, sizeof(buf));

  if (result < 0) {
    fprintf(stderr,
            "%s: stk500v2_loadaddr(): failed to set load address\n",
            progname);
    return -1;
  }

  return 0;
}
