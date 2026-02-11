SaveScanData (unsigned char *out_buf,
                   unsigned short us1Cnt,
                   unsigned short usDy,
                   unsigned short usPosX10,
                   unsigned short usPosX01,
                   unsigned short usWarp)
{
  short   sDisX;
  long  lRet;

  sDisX = (int)usPosX01 - (int)usPosX10;


  if ( (usDy > 3) || (us1Cnt > 4095) )
  {
    Save6Bytes(out_buf, usDy, us1Cnt, sDisX, usWarp);
    lRet = 6;
  }

  else if ( (usDy > 1) || (us1Cnt > 63) || (sDisX > 127) || (sDisX < -128) )
  {
    Save4Bytes(out_buf, usDy, us1Cnt, sDisX);
    lRet = 4;
  }

  else
  {
    Save2Bytes(out_buf, usDy, us1Cnt, sDisX);
    lRet = 2;
  }
  return(lRet);
}
