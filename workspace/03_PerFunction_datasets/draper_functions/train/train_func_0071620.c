check_regression (void)
{
  mpfr_t x, y;
  mpz_t  z;
  int res1, res2;

  mpz_init_set_ui (z, 2026876995);
  mpfr_init2 (x, 122);
  mpfr_init2 (y, 122);

  mpfr_set_str_binary (x, "0.10000010010000111101001110100101101010011110011100001111000001001101000110011001001001001011001011010110110110101000111011E1");
  res1 = mpfr_pow_z (y, x, z, MPFR_RNDU);
  res2 = mpfr_pow_ui (x, x, 2026876995UL, MPFR_RNDU);
  if (mpfr_cmp (x, y) || res1 != res2)
    {
      printf ("Regression (1) tested failed (%d=?%d)\n",res1, res2);
      printf ("pow_ui: "); mpfr_dump (x);
      printf ("pow_z:  "); mpfr_dump (y);

      exit (1);
    }

  mpfr_clear (x);
  mpfr_clear (y);
  mpz_clear (z);
}
