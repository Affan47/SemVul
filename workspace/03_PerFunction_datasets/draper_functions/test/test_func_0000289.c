check_single (void)
{
  mpz_t  x;
  int    limb, offset, initial;
  unsigned long  bit;

  mpz_init (x);

  for (limb = 0; limb < 4; limb++)
    {
      for (offset = (limb==0 ? 0 : -2); offset <= 2; offset++)
	{
	  for (initial = 1; initial >= -1; initial--)
	    {
	      mpz_set_si (x, (long) initial);

	      bit = (unsigned long) limb*GMP_LIMB_BITS + offset;

	      mpz_clrbit (x, bit);
	      MPZ_CHECK_FORMAT (x);
	      if (mpz_tstbit (x, bit) != 0)
		{
		  printf ("check_single(): expected 0\n");
		  abort ();
		}

	      mpz_setbit (x, bit);
	      MPZ_CHECK_FORMAT (x);
	      if (mpz_tstbit (x, bit) != 1)
		{
		  printf ("check_single(): expected 1\n");
		  abort ();
		}

	      mpz_clrbit (x, bit);
	      MPZ_CHECK_FORMAT (x);
	      if (mpz_tstbit (x, bit) != 0)
		{
		  printf ("check_single(): expected 0\n");
		  abort ();
		}

	      mpz_combit (x, bit);
	      MPZ_CHECK_FORMAT (x);
	      if (mpz_tstbit (x, bit) != 1)
		{
		  printf ("check_single(): expected 1\n");
		  abort ();
		}

	      mpz_combit (x, bit);
	      MPZ_CHECK_FORMAT (x);
	      if (mpz_tstbit (x, bit) != 0)
		{
		  printf ("check_single(): expected 0\n");
		  abort ();
		}
	    }
	}
    }

  mpz_clear (x);
}
