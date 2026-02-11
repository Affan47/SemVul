_setall(unsigned char *buf)
{
  size_t i;

  memset(buf,0xFF,nbytes - 1);

  if( nbits % 8 ){
    buf[nbytes - 1] = ~(BIT_HEX[nbits % 8 - 1] - 1);
  }else
    buf[nbytes - 1] = (unsigned char) 0xFF;
}
