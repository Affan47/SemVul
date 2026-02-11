_gcry_prime_generate (gcry_mpi_t *prime, unsigned int prime_bits,
                      unsigned int factor_bits, gcry_mpi_t **factors,
                      gcry_prime_check_func_t cb_func, void *cb_arg,
                      gcry_random_level_t random_level,
                      unsigned int flags)
{
  gcry_err_code_t rc = 0;
  gcry_mpi_t *factors_generated = NULL;
  gcry_mpi_t prime_generated = NULL;
  unsigned int mode = 0;

  if (!prime)
    return GPG_ERR_INV_ARG;
  *prime = NULL;

  if (flags & GCRY_PRIME_FLAG_SPECIAL_FACTOR)
    mode = 1;


  rc = prime_generate_internal ((mode==1), &prime_generated, prime_bits,
                                factor_bits, NULL,
                                factors? &factors_generated : NULL,
                                random_level, flags, 1,
                                cb_func, cb_arg);

  if (!rc && cb_func)
    {

      if ( !cb_func (cb_arg, GCRY_PRIME_CHECK_AT_FINISH, prime_generated))
        {

          unsigned int i;

          mpi_free (prime_generated);
          if (factors)
            {
              for (i = 0; factors_generated[i]; i++)
                mpi_free (factors_generated[i]);
              xfree (factors_generated);
            }
          rc = GPG_ERR_GENERAL;
        }
    }

  if (!rc)
    {
      if (factors)
        *factors = factors_generated;
      *prime = prime_generated;
    }

  return rc;
}
