check_rand (void)
{
  gmp_randstate_ptr rands = RANDS;
  int     i;
  mpz_t   z;
  double  got;
  long    got_exp;
  unsigned long  bits;

  mpz_init (z);

  for (i = 0; i < 200; i++)
    {
      bits = gmp_urandomm_ui (rands, 512L);
      mpz_urandomb (z, rands, bits);

      got = mpz_get_d_2exp (&got_exp, z);
      if (mpz_sgn (z) == 0)
        continue;
      bits = mpz_sizeinbase (z, 2);

      if (got < 0.5 || got >= 1.0)
        {
          printf    ("mpz_get_d_2exp out of range, expect 0.5 <= got < 1.0\n");
          mpz_trace ("   z    ", z);
          d_trace   ("   got  ", got);
          printf    ("   got exp  %ld\n", got_exp);
          abort();
        }


#if 0
      if (got_exp != bits)
        {
          printf    ("mpz_get_d_2exp wrong exponent\n", i);
          mpz_trace ("   z    ", z);
          d_trace   ("   bits ", bits);
          d_trace   ("   got  ", got);
          printf    ("   got exp  %ld\n", got_exp);
          abort();
        }
#endif
    }
  mpz_clear (z);
}
