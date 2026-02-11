_ogg_crc_entry(unsigned long index) {
  int           i;
  unsigned long r;

  r = index << 24;
  for (i=0; i<8; i++)
    if (r & 0x80000000UL)
      r = (r << 1) ^ 0x04c11db7;
    else
       r<<=1;
 return (r & 0xffffffffUL);
}
