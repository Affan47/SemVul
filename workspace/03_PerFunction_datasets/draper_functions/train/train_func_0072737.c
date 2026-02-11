mpfr_nexttoinf (mpfr_ptr x)
{
  if (MPFR_UNLIKELY(MPFR_IS_INF(x)))
    return;
  else if (MPFR_UNLIKELY(MPFR_IS_ZERO(x)))
    mpfr_setmin (x, __gmpfr_emin);
  else
    {
      mp_size_t xn;
      int sh;
      mp_limb_t *xp;

      xn = MPFR_LIMB_SIZE (x);
      MPFR_UNSIGNED_MINUS_MODULO (sh, MPFR_PREC(x));
      xp = MPFR_MANT(x);
      if (MPFR_UNLIKELY( mpn_add_1 (xp, xp, xn, MPFR_LIMB_ONE << sh)) )

        {
          mpfr_exp_t exp = MPFR_EXP (x);
          if (MPFR_UNLIKELY(exp == __gmpfr_emax))
            MPFR_SET_INF(x);
          else
            {
              MPFR_SET_EXP (x, exp + 1);
              xp[xn-1] = MPFR_LIMB_HIGHBIT;
            }
        }
    }
}
