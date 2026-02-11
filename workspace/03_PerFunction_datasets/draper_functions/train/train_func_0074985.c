CLatmDemux_GetValue(HANDLE_FDK_BITSTREAM bs)
{
  UCHAR bytesForValue = 0, tmp = 0;
  int value = 0;

  bytesForValue = (UCHAR) FDKreadBits(bs,2);

  for (UINT i=0; i<=bytesForValue; i++) {
    value <<= 8;
    tmp = (UCHAR) FDKreadBits(bs,8);
    value += tmp;
  }

  return value;
}
