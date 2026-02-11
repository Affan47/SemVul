check_special (void)
{
  mpfr_t x;
  int ret = 0;

  mpfr_init (x);
  MPFR_SET_ZERO (x);
  if ((mpfr_sgn) (x) != 0 || mpfr_sgn (x) != 0)
    {
      printf("Sgn error for 0.\n");
      ret = 1;
    }
  MPFR_SET_INF (x);
  MPFR_SET_POS (x);
  if ((mpfr_sgn) (x) != 1 || mpfr_sgn (x) != 1)
    {
      printf("Sgn error for +Inf.\n");
      ret = 1;
    }
  MPFR_SET_INF (x);
  MPFR_SET_NEG (x);
  if ((mpfr_sgn) (x) != -1 || mpfr_sgn (x) != -1)
    {
      printf("Sgn error for -Inf.\n");
      ret = 1;
    }
  MPFR_SET_NAN (x);
  mpfr_clear_flags ();
  if ((mpfr_sgn) (x) != 0 || !mpfr_erangeflag_p ())
    {
      printf("Sgn error for NaN.\n");
      ret = 1;
    }
  mpfr_clear_flags ();
  if (mpfr_sgn (x) != 0 || !mpfr_erangeflag_p ())
    {
      printf("Sgn error for NaN.\n");
      ret = 1;
    }
  mpfr_clear (x);
  if (ret)
    exit (ret);
}
