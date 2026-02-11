check_exp10(void)
{
  mpfr_t x;
  int inexact;

  mpfr_init2 (x, 200);
  mpfr_set_ui(x, 4, MPFR_RNDN);

  inexact = mpfr_exp10 (x, x, MPFR_RNDN);
  if (mpfr_cmp_ui(x, 10*10*10*10))
    {
      printf ("exp10: Wrong returned value\n");
      exit (1);
    }
  if (inexact != 0)
    {
      printf ("exp10: Wrong inexact flag\n");
      exit (1);
    }

  mpfr_clear (x);
}
