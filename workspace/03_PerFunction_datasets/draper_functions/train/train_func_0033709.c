calcCRC (HANDLE_CRC hCrcBuf, ULONG bValue, int nBits)
{
  int i;
  ULONG bMask = (1UL << (nBits - 1));

  for (i = 0; i < nBits; i++, bMask >>= 1) {
    USHORT flag = (hCrcBuf->crcState & hCrcBuf->crcMask) ? 1 : 0;
    USHORT flag1 = (bMask & bValue) ? 1 : 0;

    flag ^= flag1;
    hCrcBuf->crcState <<= 1;
    if (flag)
      hCrcBuf->crcState ^= hCrcBuf->crcPoly;
  }

  return (hCrcBuf->crcState);
}
