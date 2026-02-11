mpfr_ui_div (mpfr_ptr y, unsigned long int u, mpfr_srcptr x, mpfr_rnd_t rnd_mode)
{
  mpfr_t uu;
  mp_limb_t up[1];
  unsigned long cnt;

  MPFR_LOG_FUNC
    (("u=%lu x[%Pu]=%.*Rg rnd=%d",
      u, mpfr_get_prec(x), mpfr_log_prec, x, rnd_mode),
     ("y[%Pu]=%.*Rg", mpfr_get_prec(y), mpfr_log_prec, y));

  if (MPFR_UNLIKELY(MPFR_IS_SINGULAR(x)))
    {
      if (MPFR_IS_NAN(x))
        {
          MPFR_SET_NAN(y);
          MPFR_RET_NAN;
        }
      else if (MPFR_IS_INF(x))
        {
          MPFR_SET_ZERO(y);
          MPFR_SET_SAME_SIGN(y,x);
          MPFR_RET(0);
        }
      else
        {
          MPFR_ASSERTD(MPFR_IS_ZERO(x));
          if (u)
            {

              MPFR_SET_SAME_SIGN(y, x);
              MPFR_SET_INF(y);
              mpfr_set_divby0 ();
              MPFR_RET(0);
            }
          else
            {

              MPFR_SET_NAN(y);
              MPFR_RET_NAN;
            }
        }
    }
  else if (MPFR_LIKELY(u != 0))
    {
      MPFR_TMP_INIT1(up, uu, GMP_NUMB_BITS);
      MPFR_ASSERTN(u == (mp_limb_t) u);
      count_leading_zeros(cnt, (mp_limb_t) u);
      up[0] = (mp_limb_t) u << cnt;
      MPFR_SET_EXP (uu, GMP_NUMB_BITS - cnt);
      return mpfr_div (y, uu, x, rnd_mode);
    }
  else
    {
      MPFR_SET_ZERO(y);
      MPFR_SET_SAME_SIGN(y, x);
      MPFR_RET(0);
    }
}
