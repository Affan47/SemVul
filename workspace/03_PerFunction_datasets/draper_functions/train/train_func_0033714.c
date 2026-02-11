check_ui_range (void)
{
  unsigned long  got;
  mpz_t  x;
  int  i;

  mpz_init_set_ui (x, ULONG_MAX);

  for (i = 0; i < 20; i++)
    {
      mpz_mul_2exp (x, x, 1L);
      got = mpz_gcd_ui (NULL, x, 0L);
      if (got != 0)
        {
          printf ("mpz_gcd_ui (ULONG_MAX*2^%d, 0)\n", i);
          printf ("   return %#lx\n", got);
          printf ("   should be 0\n");
          abort ();
        }
    }

  mpz_clear (x);
}
