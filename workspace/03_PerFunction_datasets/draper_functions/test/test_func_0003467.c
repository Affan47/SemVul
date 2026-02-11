gfp_ext_print (const mpres_t r_x, const mpres_t r_y, mpmod_t modulus,
	       const int verbose)
{
  mpz_t t1, t2;

  if (!test_verbose (verbose))
    return;

  mpz_init (t1);
  mpz_init (t2);
  mpres_get_z (t1, r_x, modulus);
  mpres_get_z (t2, r_y, modulus);
  outputf (verbose, "Mod(%Zd, N) + Mod(%Zd, N) * w", t1, t2);

  mpz_clear (t1);
  mpz_clear (t2);
}
