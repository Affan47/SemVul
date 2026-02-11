HcrGetABitFromBitstream(HANDLE_FDK_BITSTREAM  bs,
                             USHORT               *pLeftStartOfSegment,
                             USHORT               *pRightStartOfSegment,
                             UCHAR                 readDirection)
{
  UINT   bit;
  INT    readBitOffset;

  if (readDirection == FROM_LEFT_TO_RIGHT) {
    readBitOffset = *pLeftStartOfSegment-FDKgetBitCnt(bs);
    if( readBitOffset ) {
      FDKpushBiDirectional(bs, readBitOffset);
    }

    bit = FDKreadBits(bs, 1);

    *pLeftStartOfSegment += 1;
  }
  else {
    readBitOffset = *pRightStartOfSegment-FDKgetBitCnt(bs);
    if( readBitOffset ) {
      FDKpushBiDirectional(bs, readBitOffset);
    }


    bit = FDKreadBits(bs, 1);
    FDKpushBack(bs, 2);

    *pRightStartOfSegment -= 1;
  }


#if ERROR_GENERATOR_BIT_STREAM_HCR
  static int a;
  if ((++a % MODULO_DIVISOR_HCR) == 0) {
    bit = (bit == 0) ? 1 : 0;
  }
#endif

  return (bit);
}
