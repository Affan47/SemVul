transportEnc_CrcStartReg(HANDLE_TRANSPORTENC hTpEnc, int mBits)
{
  int crcReg = 0;

  switch (hTpEnc->transportFmt) {
  case TT_MP4_ADTS:
    crcReg = adtsWrite_CrcStartReg(&hTpEnc->writer.adts, &hTpEnc->bitStream, mBits);
    break;
  default:
    break;
  }

  return crcReg;
}
