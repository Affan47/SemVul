check_params (void)
{
  gmp_randstate_t r1, r2;
  mpz_t a, b, m;
  int i;
  int result;

  result = TRUE;

  mpz_init (a);
  mpz_init (b);
  mpz_init (m);

  if (result)
    {

      gmp_randinit_default (r1);
      gmp_randinit_default (r2);
      gmp_randseed_ui (r1, 85L);
      gmp_randseed_ui (r2, 85L);
      mpz_set_ui (m, 0L);
      mpz_setbit (m, 80L);
      for (i = 0; i < 100; i++)
	{
	  mpz_urandomm (a, r1, m);
	  mpz_urandomb (b, r2, 80L);
	  if (mpz_cmp (a, b) != 0)
	    {
	      result = FALSE;
	      printf ("mpz_urandomm != mpz_urandomb\n");
	      break;
	    }
	}
      gmp_randclear (r1);
      gmp_randclear (r2);
    }

  if (result)
    {


      mpz_set_ui (a, 0L);
      gmp_randinit_lc_2exp (r1, a, 0xffL, 8L);
      mpz_set_ui (m, 5L);

      for (i = 0; i < 100; i++)
	{
	  mpz_urandomm (a, r1, m);
	  if (mpz_cmp_ui (a, 2L) != 0)
	    {
	      result = FALSE;
	      gmp_printf ("mpz_urandomm returns %Zd instead of 2\n", a);
	      break;
	    }
	}
      gmp_randclear (r1);
    }

  if (result)
    {


      gmp_randinit_default (r1);
      mpz_set_ui (m, 5L);
      mpz_set_si (b, -5L);
      for (i = 0; i < 100; i++)
	{
	  mpz_urandomm (a, r1, m);
	  if (mpz_cmp_ui (a, 5L) >= 0 || mpz_sgn (a) < 0)
	    {
	      result = FALSE;
	      gmp_printf ("Out-of-range or non-positive value: %Zd\n", a);
	      break;
	    }
	  mpz_urandomm (a, r1, b);
	  if (mpz_cmp_ui (a, 5L) >= 0 || mpz_sgn (a) < 0)
	    {
	      result = FALSE;
	      gmp_printf ("Out-of-range or non-positive value (from negative modulus): %Zd\n", a);
	      break;
	    }
	}
      gmp_randclear (r1);
    }

  if (result)
    {

      gmp_randinit_default (r1);
      mpz_set_ui (m, 1L);
      for (i = 0; i < 100; i++)
	{
	  mpz_urandomm (a, r1, m);
	  if (mpz_sgn (a) != 0)
	    {
	      result = FALSE;
	      gmp_printf ("mpz_urandomm fails with m=1 (result=%Zd)\n", a);
	      break;
	    }
	}
      gmp_randclear (r1);
    }

  mpz_clear (a);
  mpz_clear (b);
  mpz_clear (m);
  return result;
}
