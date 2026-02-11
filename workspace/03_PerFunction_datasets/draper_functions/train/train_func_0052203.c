refmpz_kronecker (mpz_srcptr a_orig, mpz_srcptr b_orig)
{
  unsigned long  twos;
  mpz_t  a, b;
  int    result_bit1 = 0;

  if (mpz_sgn (b_orig) == 0)
    return JACOBI_Z0 (a_orig);

  if (mpz_sgn (a_orig) == 0)
    return JACOBI_0Z (b_orig);

  if (mpz_even_p (a_orig) && mpz_even_p (b_orig))
    return 0;

  if (mpz_cmp_ui (b_orig, 1) == 0)
    return 1;

  mpz_init_set (a, a_orig);
  mpz_init_set (b, b_orig);

  if (mpz_sgn (b) < 0)
    {
      result_bit1 ^= JACOBI_BSGN_ZZ_BIT1 (a, b);
      mpz_neg (b, b);
    }
  if (mpz_even_p (b))
    {
      twos = mpz_scan1 (b, 0L);
      mpz_tdiv_q_2exp (b, b, twos);
      result_bit1 ^= JACOBI_TWOS_U_BIT1 (twos, PTR(a)[0]);
    }

  if (mpz_sgn (a) < 0)
    {
      result_bit1 ^= JACOBI_N1B_BIT1 (PTR(b)[0]);
      mpz_neg (a, a);
    }
  if (mpz_even_p (a))
    {
      twos = mpz_scan1 (a, 0L);
      mpz_tdiv_q_2exp (a, a, twos);
      result_bit1 ^= JACOBI_TWOS_U_BIT1 (twos, PTR(b)[0]);
    }

  for (;;)
    {
      ASSERT (mpz_odd_p (a));
      ASSERT (mpz_odd_p (b));
      ASSERT (mpz_sgn (a) > 0);
      ASSERT (mpz_sgn (b) > 0);

      TRACE (printf ("top\n");
	     mpz_trace (" a", a);
	     mpz_trace (" b", b));

      if (mpz_cmp (a, b) < 0)
	{
	  TRACE (printf ("swap\n"));
	  mpz_swap (a, b);
	  result_bit1 ^= JACOBI_RECIP_UU_BIT1 (PTR(a)[0], PTR(b)[0]);
	}

      if (mpz_cmp_ui (b, 1) == 0)
	break;

      mpz_sub (a, a, b);
      TRACE (printf ("sub\n");
	     mpz_trace (" a", a));
      if (mpz_sgn (a) == 0)
	goto zero;

      twos = mpz_scan1 (a, 0L);
      mpz_fdiv_q_2exp (a, a, twos);
      TRACE (printf ("twos %lu\n", twos);
	     mpz_trace (" a", a));
      result_bit1 ^= JACOBI_TWOS_U_BIT1 (twos, PTR(b)[0]);
    }

  mpz_clear (a);
  mpz_clear (b);
  return JACOBI_BIT1_TO_PN (result_bit1);

 zero:
  mpz_clear (a);
  mpz_clear (b);
  return 0;
}
