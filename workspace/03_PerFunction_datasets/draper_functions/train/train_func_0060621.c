vbitset_andn_or_cmp (bitset dst, bitset src1, bitset src2, bitset src3)
{
  unsigned int i;
  int changed = 0;
  bitset_word *src1p;
  bitset_word *src2p;
  bitset_word *src3p;
  bitset_word *dstp;
  bitset_windex size;

  if (BITSET_NBITS_ (src1) != BITSET_NBITS_ (src2)
      || BITSET_NBITS_ (src1) != BITSET_NBITS_ (src3))
    return bitset_andn_or_cmp_ (dst, src1, src2, src3);

  vbitset_resize (dst, BITSET_NBITS_ (src1));

  src1p = VBITSET_WORDS (src1);
  src2p = VBITSET_WORDS (src2);
  src3p = VBITSET_WORDS (src3);
  dstp = VBITSET_WORDS (dst);
  size = VBITSET_SIZE (dst);

  for (i = 0; i < size; i++, dstp++)
    {
      bitset_word tmp = (*src1p++ & ~(*src2p++)) | *src3p++;

      if (*dstp != tmp)
        {
          changed = 1;
          *dstp = tmp;
        }
    }
  return changed;
}
