gabufr_readbits2num(unsigned char * pos, gaint offset, gaint bitcnt) {
  long retval;
  if (bitcnt <= 0 || bitcnt > sizeof(long) * 8) {
    printf("warning: can't read %d-bit data value; max is %d\n",
	   bitcnt, (gaint) (sizeof(long) * 8));
    return gabufr_all_ones(bitcnt);
  } else {
    retval = gagbb(pos, offset, bitcnt);
    if (GABUFR_DEBUG) printf("read %2d bits at (%p + %d):  %ld\n",
			     bitcnt, pos, offset, retval);
    return retval;
  }
}
