encode(
	   unsigned char *symbols,
	   unsigned char *data,
	   unsigned int nbytes)
{
  unsigned long encstate;
  int sym;
  int i;

  encstate = 0;
  while(nbytes-- != 0) {
    for(i=7;i>=0;i--) {
      encstate = (encstate << 1) | ((*data >> i) & 1);
      ENCODE(sym,encstate);
      *symbols++ = sym >> 1;
      *symbols++ = sym & 1;
    }
    data++;
  }
  return 0;
}
