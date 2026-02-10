gt_bsStoreUInt8(BitString str, BitOffset offset,
                 unsigned numBits, uint8_t val)
{
  unsigned bitsLeft = numBits,
    bitTop = offset%bitElemBits;
  size_t elemStart = offset/bitElemBits;
  BitElem *p = str + elemStart;
  gt_assert(str);
  gt_assert(numBits <= sizeof (val)*CHAR_BIT);

  if (bitTop)
  {
    unsigned long mask = ~(unsigned long)0;
    if (bitElemBits < (sizeof (unsigned long)*CHAR_BIT))
    {
      mask <<= bitElemBits;
    }
    else
    {
      mask = 0;
    }
    mask = (~mask) >> bitTop;
    if (numBits < bitElemBits - bitTop)
    {
      unsigned backShift = bitElemBits - numBits - bitTop;
      mask &= ~(unsigned long)0 << backShift;
      *p = (*p & ~mask) | ((val << backShift) & mask);

      return;
    }
    else
    {
      bitsLeft -= bitElemBits - bitTop;
      *p = (*p & ~mask) | ((val >> bitsLeft) & mask);
      ++p;
    }
  }

  while (bitsLeft >= bitElemBits)
  {
    bitsLeft -= bitElemBits;
    *p++ = val >> bitsLeft;
  }

  if (bitsLeft)
  {
    unsigned long mask =
      ((~(unsigned long)0)<<(bitElemBits - bitsLeft));
    if (bitElemBits < (sizeof (unsigned long)*CHAR_BIT))
      mask &= (~(~(unsigned long)0<<bitElemBits));
    *p = (*p & ~mask) | ((val << (bitElemBits - bitsLeft)) & mask);
  }
}
