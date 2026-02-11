mpfr_div_2ui (mpfr_ptr y, mpfr_srcptr x, unsigned long n, mpfr_rnd_t rnd_mode)
{
  int inexact;

  MPFR_LOG_FUNC (
    ("x[%Pu]=%.*Rg n=%lu rnd=%d", mpfr_get_prec(x), mpfr_log_prec, x, n,
     rnd_mode),
    ("y[%Pu]=%.*Rg inexact=%d", mpfr_get_prec(y), mpfr_log_prec, y, inexact));

  if (MPFR_UNLIKELY (MPFR_IS_SINGULAR (x)))
    return mpfr_set (y, x, rnd_mode);
  else
    {
      mpfr_exp_t exp = MPFR_GET_EXP (x);
      mpfr_uexp_t diffexp;

      MPFR_SETRAW (inexact, y, x, exp, rnd_mode);
      diffexp = (mpfr_uexp_t) exp - (mpfr_uexp_t) (__gmpfr_emin - 1);
      if (MPFR_UNLIKELY (n >= diffexp))
        {
          if (rnd_mode == MPFR_RNDN &&
              (n > diffexp || (inexact >= 0 && mpfr_powerof2_raw (y))))
            rnd_mode = MPFR_RNDZ;
          return mpfr_underflow (y, rnd_mode, MPFR_SIGN (y));
        }

      while (n > LONG_MAX)
        {
          n -= LONG_MAX;
          exp -= LONG_MAX;
        }
      MPFR_SET_EXP (y, exp - (long) n);
    }

  MPFR_RET (inexact);
}
