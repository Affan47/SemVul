tune_mpres_sqr (mp_size_t limbs, int repr)
{
  mpmod_t modulus;
  mpres_t x, z;
  mpz_t N, p;
  unsigned int __k = 1, __i;
  long __st;

  mpz_init (N);
  mpz_init (p);


  do
    {
      mpz_urandomb (N, gmp_randstate, limbs * GMP_NUMB_BITS);
      while (mpz_gcd_ui (NULL, N, 6) != 1)
        mpz_add_ui (N, N, 1);
    }
  while ((mp_size_t) mpz_size (N) != limbs);

  if (repr == ECM_MOD_MPZ)
    mpmod_init_MPZ (modulus, N);
  else if (repr == ECM_MOD_MODMULN)
    mpmod_init_MODMULN (modulus, N);
  else if (repr == ECM_MOD_REDC)
    mpmod_init_REDC (modulus, N);

  mpz_urandomm (p, gmp_randstate, N);

  mpres_init (x, modulus);
  mpres_init (z, modulus);

  mpres_set_z (x, p, modulus);

  TUNE_FUNC_LOOP (mpres_sqr (z, x, modulus));

  mpres_clear (x, modulus);
  mpres_clear (z, modulus);
  mpmod_clear (modulus);
  mpz_clear (N);
  mpz_clear (p);

  return (double) __k / (double) __st;
}
