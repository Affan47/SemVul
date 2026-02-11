hexString2CharBuf(const char *string, UCHAR *charBuf, UINT charBufLength)
{
  UINT i, k = 0;
  UCHAR hNibble, lNibble;


  if (string[0] == '\0') {
    return -1;
  }

  if (charBufLength<=0){
    return -2;
  }


  for (i=0;(string[i]!='\0')&&((i>>1)<charBufLength);i+=2) {
    k = i>>1;
    hNibble = hexChar2Dec(string[i]);
    lNibble = hexChar2Dec(string[i+1]);
    if ((hNibble == 16) || (lNibble == 16)) {
      return -3;
    }
    charBuf[k] = ((hNibble<<4)&0xf0) + lNibble;
  }


  if ((string[i-2]!=0) && (string[i]!=0)) {
    return -1;
  }


  for (i=k+1;i<charBufLength;i++) {
    charBuf[i] = 0;
  }

  return 0;

}
