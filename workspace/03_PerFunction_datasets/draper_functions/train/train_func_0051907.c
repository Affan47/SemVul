getnanf(void)
#else
float getnanf()
#endif
{
  unsigned char nan[4];
  int i;

  for(i=0; i<4; i++)
    nan[i] = 1;

  if( is_bigendian() ){
    nan[0] = 0x7F;
    nan[1] = 0x80;
  }
  else{
    nan[3] = 0x7F;
    nan[2] = 0x80;
  }

  return(*((float *)nan));
}
