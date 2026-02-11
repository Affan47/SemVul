mpfr_nexttozero (mpfr_ptr x)
{
  if (MPFR_UNLIKELY(MPFR_IS_INF(x)))
    {
      mpfr_setmax (x, __gmpfr_emax);
      return;
    }
  else if (MPFR_UNLIKELY( MPFR_IS_ZERO(x) ))
    {
      MPFR_CHANGE_SIGN(x);
      mpfr_setmin (x, __gmpfr_emin);
    }
  else
    {
      mp_size_t xn;
      int sh;
      mp_limb_t *xp;

      xn = MPFR_LIMB_SIZE (x);
      MPFR_UNSIGNED_MINUS_MODULO (sh, MPFR_PREC(x));
      xp = MPFR_MANT(x);
      mpn_sub_1 (xp, xp, xn, MPFR_LIMB_ONE << sh);
      if (MPFR_UNLIKELY( MPFR_LIMB_MSB(xp[xn-1]) == 0) )
        {
          mpfr_exp_t exp = MPFR_EXP (x);
          if (MPFR_UNLIKELY(exp == __gmpfr_emin))
            MPFR_SET_ZERO(x);
          else
            {
              mp_size_t i;
              MPFR_SET_EXP (x, exp - 1);
              xp[0] = MP_LIMB_T_MAX << sh;
              for (i = 1; i < xn; i++)
                xp[i] = MP_LIMB_T_MAX;
            }
        }
    }
}
