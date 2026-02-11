check_ieee_denorm (void)
{
  static long exp;
  mp_limb_t  n = 1;
  long       i;
  mp_size_t  sign;
  double     want, got;

  if (! _GMP_IEEE_FLOATS)
    return;

  if (tests_setjmp_sigfpe() == 0)
    {
      exp = -1020;
      want = 1.0;
      for (i = 0; i > exp; i--)
        want *= 0.5;

      for ( ; exp > -1500 && want != 0.0; exp--)
        {
          for (sign = 0; sign >= -1; sign--)
            {
              got = mpn_get_d (&n, (mp_size_t) 1, sign, exp);
              if (got != want)
                {
                  printf  ("mpn_get_d wrong on denorm\n");
                  printf  ("  n=1\n");
                  printf  ("  exp   %ld\n", exp);
                  printf  ("  sign  %ld\n", (long) sign);
                  d_trace ("  got   ", got);
                  d_trace ("  want  ", want);
                  abort ();
                }
              want = -want;
            }
          want *= 0.5;
          FORCE_DOUBLE (want);
        }
    }
  else
    {
      printf ("Warning, IEEE denorm tests skipped due to SIGFPE (exp=%ld)\n", exp);
    }
  tests_sigfpe_done ();
}
