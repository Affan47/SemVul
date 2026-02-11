generic_acer(unsigned int *dst, const unsigned int lng)
{
  int i;
  for(i=0;(i<lng)&&(dst[i]!=VAL_STOP);i++)
  {
    dst[i]=dst[i]>>1;
  }


}
