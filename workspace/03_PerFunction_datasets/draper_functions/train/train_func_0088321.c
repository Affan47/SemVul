mpfr_li2_asympt_pos (mpfr_ptr y, mpfr_srcptr x, mpfr_rnd_t rnd_mode)
{
  mpfr_t g, h;
  mpfr_prec_t w = MPFR_PREC (y) + 20;
  int inex = 0;

  MPFR_ASSERTN (mpfr_cmp_ui (x, 38) >= 0);

  mpfr_init2 (g, w);
  mpfr_init2 (h, w);
  mpfr_log (g, x, MPFR_RNDN);
  mpfr_sqr (g, g, MPFR_RNDN);
  mpfr_div_2ui (g, g, 1, MPFR_RNDN);
  mpfr_const_pi (h, MPFR_RNDN);
  mpfr_sqr (h, h, MPFR_RNDN);
  mpfr_div_ui (h, h, 3, MPFR_RNDN);


  MPFR_ASSERTN (MPFR_EXP (g) > MPFR_EXP (h));
  mpfr_sub (g, h, g, MPFR_RNDN);


  if ((MPFR_EXP (x) >= (mpfr_exp_t) w - MPFR_EXP (g)) &&
      MPFR_CAN_ROUND (g, w - 4, MPFR_PREC (y), rnd_mode))
    inex = mpfr_set (y, g, rnd_mode);

  mpfr_clear (g);
  mpfr_clear (h);

  return inex;
}
