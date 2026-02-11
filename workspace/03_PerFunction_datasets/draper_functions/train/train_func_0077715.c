FillDistancesPrices(CLzmaEnc *p)
{
  LZ_UInt32 tempPrices[kNumFullDistances];
  LZ_UInt32 i, lenToPosState;
  for (i = kStartPosModelIndex; i < kNumFullDistances; i++)
  {
    LZ_UInt32 posSlot = GetPosSlot1(i);
    LZ_UInt32 footerBits = ((posSlot >> 1) - 1);
    LZ_UInt32 base = ((2 | (posSlot & 1)) << footerBits);
    tempPrices[i] = RcTree_ReverseGetPrice(p->posEncoders + base - posSlot - 1, footerBits, i - base, p->ProbPrices);
  }

  for (lenToPosState = 0; lenToPosState < kNumLenToPosStates; lenToPosState++)
  {
    LZ_UInt32 posSlot;
    const CLzmaProb *encoder = p->posSlotEncoder[lenToPosState];
    LZ_UInt32 *posSlotPrices = p->posSlotPrices[lenToPosState];
    for (posSlot = 0; posSlot < p->distTableSize; posSlot++)
      posSlotPrices[posSlot] = RcTree_GetPrice(encoder, kNumPosSlotBits, posSlot, p->ProbPrices);
    for (posSlot = kEndPosModelIndex; posSlot < p->distTableSize; posSlot++)
      posSlotPrices[posSlot] += ((((posSlot >> 1) - 1) - kNumAlignBits) << kNumBitPriceShiftBits);

    {
      LZ_UInt32 *distancesPrices = p->distancesPrices[lenToPosState];
      LZ_UInt32 i;
      for (i = 0; i < kStartPosModelIndex; i++)
        distancesPrices[i] = posSlotPrices[i];
      for (; i < kNumFullDistances; i++)
        distancesPrices[i] = posSlotPrices[GetPosSlot1(i)] + tempPrices[i];
    }
  }
  p->matchPriceCount = 0;
}
