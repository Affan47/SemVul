special (void)
{
  mpfr_t x, y;

  mpfr_init (x);
  mpfr_init (y);

  MPFR_SET_INF(x);
  mpfr_set_ui (y, 1, MPFR_RNDN);
  mpfr_acosh (x, y, MPFR_RNDN);
  if (MPFR_IS_INF(x) || MPFR_IS_NAN(x) )
    {
      printf ("Inf flag not clears in acosh!\n");
      exit (1);
    }
  if (mpfr_cmp_ui (x, 0))
    {
      printf ("Error: mpfr_acosh(1) <> 0\n");
      exit (1);
    }

  MPFR_SET_NAN(x);
  mpfr_acosh (x, y, MPFR_RNDN);
  if (MPFR_IS_NAN(x) || MPFR_IS_INF(x) )
    {
      printf ("NAN flag not clears in acosh!\n");
      exit (1);
    }

  mpfr_set_ui (x, 0, MPFR_RNDN);
  mpfr_acosh (y, x, MPFR_RNDN);
  if (!mpfr_nan_p (y))
    {
      printf ("Error: mpfr_acosh(0) <> NaN\n");
      exit (1);
    }

  mpfr_set_si (x, -1, MPFR_RNDN);
  mpfr_acosh (y, x, MPFR_RNDN);
  if (!mpfr_nan_p (y))
    {
      printf ("Error: mpfr_acosh(-1) <> NaN\n");
      exit (1);
    }

  MPFR_SET_NAN(x);
  mpfr_acosh (y, x, MPFR_RNDN);
  if (!mpfr_nan_p (y))
    {
      printf ("Error: mpfr_acosh(NaN) <> NaN\n");
      exit (1);
    }

  mpfr_set_inf (x, 1);
  mpfr_acosh (y, x, MPFR_RNDN);
  if (!mpfr_inf_p (y) || mpfr_sgn (y) < 0)
    {
      printf ("Error: mpfr_acosh(+Inf) <> +Inf\n");
      exit (1);
    }

  mpfr_set_inf (x, -1);
  mpfr_acosh (y, x, MPFR_RNDN);
  if (!mpfr_nan_p (y))
    {
      printf ("Error: mpfr_acosh(-Inf) <> NaN\n");
      exit (1);
    }

  mpfr_set_ui (x, 1, MPFR_RNDN);
  mpfr_div_2exp (x, x, 1, MPFR_RNDN);
  mpfr_acosh (y, x, MPFR_RNDN);
  if (!mpfr_nan_p (y))
    {
      printf ("Error: mpfr_acosh(1/2) <> NaN\n");
      exit (1);
    }

  mpfr_set_prec (x, 32);
  mpfr_set_prec (y, 32);
  mpfr_set_str_binary (x, "1.000001101011101111001011");
  mpfr_acosh (y, x, MPFR_RNDN);
  mpfr_set_str_binary (x, "0.111010100101101001010001101001E-2");
  if (mpfr_cmp (x, y))
    {
      printf ("Error: mpfr_acosh (1)\n");
      exit (1);
    }

  mpfr_clear (x);
  mpfr_clear (y);
}
