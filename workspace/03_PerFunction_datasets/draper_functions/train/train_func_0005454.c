butterfly_read_byte_flash(PROGRAMMER * pgm, AVRPART * p, AVRMEM * m,
                                  unsigned long addr, unsigned char * value)
{
  static int cached = 0;
  static unsigned char cvalue;
  static unsigned long caddr;
  int use_ext_addr = m->op[AVR_OP_LOAD_EXT_ADDR] != NULL;

  if (cached && ((caddr + 1) == addr)) {
    *value = cvalue;
    cached = 0;
  }
  else {
    char buf[2];

    if (use_ext_addr) {
      butterfly_set_extaddr(pgm, addr >> 1);
    } else {
      butterfly_set_addr(pgm, addr >> 1);
    }

    butterfly_send(pgm, "g\000\002F", 4);


    butterfly_recv(pgm, buf, sizeof(buf));

    if ((addr & 0x01) == 0) {
      *value = buf[0];
      cached = 1;
      cvalue = buf[1];
      caddr = addr;
    }
    else {
      *value = buf[1];
    }
  }

  return 0;
}
