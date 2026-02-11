eval_power (mpz_t prior_n, mpz_t n,char op)
{
#if defined (DEBUG_EVALUATOR)
  if ('#'==op || '^'==op || '!'==op || '@'==op || '$'==op)
    {
      fprintf (stderr, "eval_power ");
      mpz_out_str(stderr, 10, prior_n);
      fprintf (stderr, "%c", op);
      mpz_out_str(stderr, 10, n);
      fprintf (stderr, "\n");
    }
#endif

  if ('^'==op)
    mpz_pow_ui(n,prior_n,mpz_get_ui(n));
  else if ('!'==op)
    mpz_fac_ui(n,mpz_get_ui(n));
  else if ('@'==op)
    {
      long nCur;
      unsigned long nDecr;
      nCur = mpz_get_si(prior_n);
      nDecr = mpz_get_ui(n);
      mpz_set_ui(n,1);

      while (nCur > 1)
	{

	  mpz_mul_ui(n,n,nCur);
	  nCur -= nDecr;
	}
    }
  else if ('#'==op)
    {
      long nMax;
      double p;
      nMax = mpz_get_si(n);
      mpz_set_ui(n,1);
      getprime_clear ();
      for (p = 2.0; p <= nMax; p = getprime ())

	mpz_mul_ui(n,n,(unsigned)p);
    }
  else if ('$'==op)
    {
      double p;
      long nMax;
      unsigned long nStart;
      nMax = mpz_get_si(prior_n);
      nStart = mpz_get_ui(n);
      mpz_set_ui(n,1);
      getprime_clear ();
      p = getprime (nStart);

      for (; p <= nMax; p = getprime (p))
	{


	  if (p >= nStart)

	    mpz_mul_ui(n,n,(unsigned)p);
	}
    }
}
