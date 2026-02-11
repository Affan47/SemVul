check_diff (void)
{
  int inex;
  mpfr_t x;
  mpz_t  z;
  mpfr_exp_t emin;

  mpz_init   (z);
  mpfr_init2 (x, 2);

  mpfr_set_ui (x, 2047, MPFR_RNDU);
  mpz_set_fr (z, x, MPFR_RNDN);
  if (mpz_cmp_ui (z, 2048) != 0)
    {
      printf ("get_z RU 2048 failed\n");
      exit (1);
    }

  mpfr_set_prec (x, 6);
  mpfr_set_str (x, "17.5", 10, MPFR_RNDN);
  inex = mpfr_get_z (z, x, MPFR_RNDN);
  if (inex <= 0 || mpz_cmp_ui (z, 18) != 0)
    {
      printf ("get_z RN 17.5 failed\n");
      exit (1);
    }


  emin = mpfr_get_emin ();;

  mpfr_set_emin (17);
  mpfr_set_ui (x, 0, MPFR_RNDN);
  inex = mpfr_get_z (z, x, MPFR_RNDN);
  if (inex != 0 || mpz_cmp_ui (z, 0) != 0)
    {
      printf ("get_z 0 failed\n");
      exit (1);
    }


  mpfr_set_emin (emin);

  mpfr_clear (x);
  mpz_clear  (z);
}
