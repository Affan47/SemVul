bug20071104 (void)
{
  mpfr_t x, y, z;
  mpfr_exp_t emin, emax;
  int inex;

  emin = mpfr_get_emin ();
  emax = mpfr_get_emax ();
  mpfr_set_emin (-1000000);
  mpfr_set_emax ( 1000000);

  mpfr_inits2 (20, x, y, z, (mpfr_ptr) 0);
  mpfr_set_ui (x, 0, MPFR_RNDN);
  mpfr_nextbelow (x);
  mpfr_set_si (y, -2, MPFR_RNDN);
  mpfr_clear_flags ();
  inex = mpfr_pow (z, x, y, MPFR_RNDN);
  if (! mpfr_inf_p (z) || MPFR_SIGN (z) < 0)
    {
      printf ("Error in bug20071104: expected +Inf, got ");
      mpfr_dump (z);
      exit (1);
    }
  if (inex <= 0)
    {
      printf ("Error in bug20071104: bad ternary value (%d)\n", inex);
      exit (1);
    }
  if (__gmpfr_flags != (MPFR_FLAGS_OVERFLOW | MPFR_FLAGS_INEXACT))
    {
      printf ("Error in bug20071104: bad flags (%u)\n", __gmpfr_flags);
      exit (1);
    }
  mpfr_clears (x, y, z, (mpfr_ptr) 0);

  set_emin (emin);
  set_emax (emax);
}
