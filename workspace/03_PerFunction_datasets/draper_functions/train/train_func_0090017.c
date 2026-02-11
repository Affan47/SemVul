mpfr_lgamma (mpfr_ptr y, int *signp, mpfr_srcptr x, mpfr_rnd_t rnd)
{
  int inex;

  MPFR_LOG_FUNC
    (("x[%Pu]=%.*Rg rnd=%d", mpfr_get_prec (x), mpfr_log_prec, x, rnd),
     ("y[%Pu]=%.*Rg signp=%d inexact=%d",
      mpfr_get_prec (y), mpfr_log_prec, y, *signp, inex));

  *signp = 1;

  if (MPFR_UNLIKELY (MPFR_IS_SINGULAR (x)))
    {
      if (MPFR_IS_NAN (x))
        {
          MPFR_SET_NAN (y);
          MPFR_RET_NAN;
        }
      else
        {
          if (MPFR_IS_ZERO (x))
            mpfr_set_divby0 ();
          *signp = MPFR_INT_SIGN (x);
          MPFR_SET_INF (y);
          MPFR_SET_POS (y);
          MPFR_RET (0);
        }
    }

  if (MPFR_IS_NEG (x))
    {
      if (mpfr_integer_p (x))
        {
          MPFR_SET_INF (y);
          MPFR_SET_POS (y);
          mpfr_set_divby0 ();
          MPFR_RET (0);
        }

      if (unit_bit (x) == 0)
        *signp = -1;


      if (MPFR_EXP(x) + 1 <= - (mpfr_exp_t) MPFR_PREC(y))


        {
          mpfr_t l, h;
          int ok, inex2;
          mpfr_prec_t w = MPFR_PREC (y) + 14;
          mpfr_exp_t expl;

          while (1)
            {
              mpfr_init2 (l, w);
              mpfr_init2 (h, w);


              mpfr_neg (l, x, MPFR_RNDU);
              mpfr_log (l, l, MPFR_RNDU);
              mpfr_neg (l, l, MPFR_RNDD);
              mpfr_neg (h, x, MPFR_RNDD);
              mpfr_log (h, h, MPFR_RNDD);
              mpfr_neg (h, h, MPFR_RNDU);
              mpfr_sub (h, h, x, MPFR_RNDU);
              inex = mpfr_prec_round (l, MPFR_PREC (y), rnd);
              inex2 = mpfr_prec_round (h, MPFR_PREC (y), rnd);


              ok = SAME_SIGN (inex, inex2) && mpfr_equal_p (l, h);
              if (ok)
                mpfr_set (y, h, rnd);
              else
                expl = MPFR_EXP (l);
              mpfr_clear (l);
              mpfr_clear (h);
              if (ok)
                return inex;


              if (expl < MPFR_EXP(x) + (mpfr_exp_t) w)
                break;
              w += MPFR_INT_CEIL_LOG2(w) + 3;
            }
        }
    }

  inex = mpfr_lngamma_aux (y, x, rnd);
  return inex;
}
