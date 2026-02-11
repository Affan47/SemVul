check_specials (void)
{
  mpfr_t  x, y;

  mpfr_init2 (x, 123L);
  mpfr_init2 (y, 123L);

  mpfr_set_nan (x);
  mpfr_sech (y, x, MPFR_RNDN);
  if (! mpfr_nan_p (y))
    {
      printf ("Error: sech(NaN) != NaN\n");
      exit (1);
    }

  mpfr_set_inf (x, 1);
  mpfr_sech (y, x, MPFR_RNDN);
  if (! (MPFR_IS_ZERO (y) && MPFR_SIGN (y) > 0))
    {
      printf ("Error: sech(+Inf) != +0\n");
      exit (1);
    }

  mpfr_set_inf (x, -1);
  mpfr_sech (y, x, MPFR_RNDN);
  if (! (MPFR_IS_ZERO (y) && MPFR_SIGN (y) > 0))
    {
      printf ("Error: sech(-Inf) != +0\n");
      exit (1);
    }


  mpfr_set_ui (x, 0, MPFR_RNDN);
  mpfr_sech (y, x, MPFR_RNDN);
  if (mpfr_cmp_ui (y, 1))
    {
      printf ("Error: sech(+0) != 1\n");
      exit (1);
    }
  mpfr_neg (x, x, MPFR_RNDN);
  mpfr_sech (y, x, MPFR_RNDN);
  if (mpfr_cmp_ui (y, 1))
    {
      printf ("Error: sech(-0) != 1\n");
      exit (1);
    }


  mpfr_set_str (x, "8e8", 10, MPFR_RNDN);
  mpfr_sech (y, x, MPFR_RNDN);
  if (! (mpfr_zero_p (y) && MPFR_SIGN (y) > 0))
    {
      printf ("Error: sech(8e8) != +0\n");
      exit (1);
    }
  mpfr_set_str (x, "-8e8", 10, MPFR_RNDN);
  mpfr_sech (y, x, MPFR_RNDN);
  if (! (mpfr_zero_p (y) && MPFR_SIGN (y) > 0))
    {
      printf ("Error: sech(-8e8) != +0\n");
      exit (1);
    }

  mpfr_clear (x);
  mpfr_clear (y);
}
