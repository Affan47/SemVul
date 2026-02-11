mask_integer(u_64 *pval, unsigned bits, unsigned shift, int extend_msb)
{
  u_64 mask;
  const unsigned msb = bits + shift - 1;

  assert(bits <= 64);
  assert(shift <= 64);
  assert((bits + shift) <= 64);

#if ARCH_NATIVE_64_BIT_INTEGER

  mask = (ALL_64_BITS >> (64 - bits)) << shift;
  *pval &= mask;

  if (extend_msb && bits > 0)
    if (*pval & (((u_64)1) << msb))
      *pval |= ALL_64_BITS << msb;

#else

  if (bits > 32)
  {
    mask.h = (ALL_32_BITS >> (64 - bits));
    mask.l = ALL_32_BITS;
  }
  else
  {
    mask.h = 0;
    mask.l = (ALL_32_BITS >> (32 - bits));
  }

  if (shift > 0)
    shift_integer(&mask, shift, SHIFT_LEFT);

  pval->h &= mask.h;
  pval->l &= mask.l;

  if (extend_msb && bits > 0)
  {
    if (msb >= 32)
    {
      if (pval->h & (((u_32)1) << (msb - 32)))
        pval->h |= ALL_32_BITS << (msb - 32);
    }
    else
    {
      if (pval->l & (((u_32)1) << msb))
      {
        pval->h  = ALL_32_BITS;
        pval->l |= ALL_32_BITS << msb;
      }
    }
  }

#endif
}
