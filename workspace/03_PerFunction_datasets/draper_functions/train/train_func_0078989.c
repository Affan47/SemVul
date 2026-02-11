encode_lps_nolearn(unsigned int z)
{
#ifdef ZPCODER
  unsigned int d = 0x6000 + ((z+a)>>2);
  if (z > d)
    z = d;
#endif
#ifdef ZCODER
  if (z >= 0x8000)
    z = 0x4000 + (z>>1);
#endif

  z = 0x10000 - z;
  subend += z;
  a += z;

  while (a >= 0x8000)
    {
      zemit(1 - (subend>>15) );
      subend = (unsigned short)(subend<<1);
      a = (unsigned short)(a<<1);
    }
}
