calcCRC(void)
{
  unsigned short uCrc16;
  unsigned char abData[2];
  unsigned int uLen = myLength;
  unsigned char * commData = (unsigned char *)myBuf;

  uCrc16 = 0;
  abData[0] = 0;
  while (uLen--)
  {
    abData[1] = abData[0];
    abData[0] = *commData++;
    if (uCrc16 & 0x8000)
    {
      uCrc16 = (uCrc16 & 0x7fff) << 1;
      uCrc16 ^= 0x8005;
    }
    else
    {
      uCrc16 <<= 1;
    }
    uCrc16 ^= ((unsigned short) abData[0] |
	       ((unsigned short)(abData[1]) << 8));
  }
  return uCrc16;
}
