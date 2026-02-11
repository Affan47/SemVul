mpfr_frexp (mpfr_exp_t *exp, mpfr_ptr y, mpfr_srcptr x, mpfr_rnd_t rnd)
{
  int inex;

  if (MPFR_UNLIKELY(MPFR_IS_SINGULAR(x)))
    {
      if (MPFR_IS_NAN(x))
        {
          MPFR_SET_NAN(y);
          MPFR_RET_NAN;
        }
      else if (MPFR_IS_INF(x))
        {
          MPFR_SET_INF(y);
          MPFR_SET_SAME_SIGN(y,x);
          MPFR_RET(0);
        }
      else
        {
          MPFR_SET_ZERO(y);
          MPFR_SET_SAME_SIGN(y,x);
          *exp = 0;
          MPFR_RET(0);
        }
    }

  inex = mpfr_set (y, x, rnd);
  *exp = MPFR_GET_EXP (y);
  MPFR_SET_EXP (y, 0);
  return mpfr_check_range (y, inex, rnd);
}
