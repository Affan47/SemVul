next_base_power_p (mpfr_srcptr x, int base, mpfr_rnd_t rnd)
{
  mpfr_prec_t nbits;
  mp_limb_t pm;
  mp_limb_t xm;

  MPFR_ASSERTD (MPFR_IS_PURE_FP (x));
  MPFR_ASSERTD (base == 2 || base == 16);


  nbits = base == 2 ? 1 : 4;

  if (rnd == MPFR_RNDZ
      || (rnd == MPFR_RNDD && MPFR_IS_POS (x))
      || (rnd == MPFR_RNDU && MPFR_IS_NEG (x))
      || MPFR_PREC (x) <= nbits)

    return 0;

  xm = MPFR_MANT (x) [MPFR_LIMB_SIZE (x) - 1];
  pm = MPFR_LIMB_MASK (GMP_NUMB_BITS - nbits);
  if ((xm & ~pm) ^ ~pm)

    return 0;

  if (rnd == MPFR_RNDN)

    pm = (MPFR_LIMB_ONE << (GMP_NUMB_BITS - nbits - 1));


  return xm & pm ? 1 : 0;
}
