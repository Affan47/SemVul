mpzspv_from_mpzv (mpzspv_t x, const spv_size_t offset, const mpzv_t mpzv,
    const spv_size_t len, mpzspm_t mpzspm)
{
  const unsigned int sp_num = mpzspm->sp_num;
  long i;

  ASSERT (mpzspv_verify (x, offset + len, 0, mpzspm));
  ASSERT (sizeof (mp_limb_t) >= sizeof (sp_t));

#if defined(_OPENMP)
#pragma omp parallel private(i) if (len > 16384)
  {

#pragma omp for schedule(static)
#endif
    for (i = 0; i < (long) len; i++)
    {
      unsigned int j;
      if (mpz_sgn (mpzv[i]) == 0)
	{
	  for (j = 0; j < sp_num; j++)
	    x[j][i + offset] = 0;
	}
      else
        {
	  ASSERT(mpz_sgn (mpzv[i]) > 0);
          if (mpzspm->T == NULL)
            mpzspv_from_mpzv_slow (x, i + offset, mpzv[i], mpzspm);
          else
            mpzspv_from_mpzv_fast (x, i + offset, mpzv[i], mpzspm);
	}
    }
#if defined(_OPENMP)
  }
#endif
}
