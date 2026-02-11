unicode(int &index) const
{
  int wch = uchar(iImp->iData[index++]);
  if ((wch & 0xc0) == 0x80) {

    while (index < iImp->iSize && (iImp->iData[index] & 0xc0) == 0x80)
      index++;
    return 0xfffd;
  }
  int extraBytes = bytesFromUTF8[wch & 0xff];
  wch -= firstByteMark[extraBytes];
  while (extraBytes--) {
    if (index >= iImp->iSize)
      return 0xfffd;
    if ((iImp->iData[index] & 0xc0) != 0x80)
      return 0xfffd;
    wch <<= 6;
    wch |= (iImp->iData[index++] & 0x3f);
  }
  return wch;
}
