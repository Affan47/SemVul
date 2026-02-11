check (long i, mpfr_rnd_t rnd)
{
  mpfr_t f;
  mpz_t z;

  mpfr_init2 (f, 8 * sizeof(long));
  mpz_init (z);
  mpz_set_ui (z, i);
  mpfr_set_z (f, z, rnd);
  if (mpfr_get_si (f, MPFR_RNDZ) != i)
    {
      printf ("Error in mpfr_set_z for i=%ld rnd_mode=%d\n", i, rnd);
      exit (1);
    }
  mpfr_clear (f);
  mpz_clear (z);
}
