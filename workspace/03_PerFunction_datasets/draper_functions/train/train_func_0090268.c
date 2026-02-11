bug20080820 (void)
{
  mpfr_exp_t emin;
  mpfr_t x, y, z1, z2;

  emin = mpfr_get_emin ();
  mpfr_set_emin (MPFR_EMIN_MIN);
  mpfr_init2 (x, 80);
  mpfr_init2 (y, sizeof (mpfr_exp_t) * CHAR_BIT + 32);
  mpfr_init2 (z1, 2);
  mpfr_init2 (z2, 80);
  mpfr_set_ui (x, 2, MPFR_RNDN);
  mpfr_nextbelow (x);
  mpfr_set_exp_t (y, mpfr_get_emin () - 2, MPFR_RNDN);
  mpfr_nextabove (y);
  mpfr_pow (z1, x, y, MPFR_RNDN);
  mpfr_pow (z2, x, y, MPFR_RNDN);


  if (MPFR_IS_ZERO (z1) && MPFR_NOTZERO (z2))
    {
      printf ("Error in bug20080820\n");
      exit (1);
    }
  mpfr_clears (x, y, z1, z2, (mpfr_ptr) 0);
  set_emin (emin);
}
