check_sgn(void)
{
  mpfr_t x;
  int i, s1, s2;

  mpfr_init(x);
  for(i = 0 ; i < 100 ; i++)
    {
      mpfr_urandomb (x, RANDS);
      if (i&1)
        {
          MPFR_SET_POS(x);
          s2 = 1;
        }
      else
        {
          MPFR_SET_NEG(x);
          s2 = -1;
        }
      s1 = mpfr_sgn(x);
      if (s1 < -1 || s1 > 1)
        {
          printf("Error for sgn: out of range.\n");
          goto lexit;
        }
      else if (MPFR_IS_NAN(x) || MPFR_IS_ZERO(x))
        {
          if (s1 != 0)
            {
              printf("Error for sgn: Nan or Zero should return 0.\n");
              goto lexit;
            }
        }
      else if (s1 != s2)
        {
          printf("Error for sgn. Return %d instead of %d.\n", s1, s2);
          goto lexit;
        }
    }
  mpfr_clear(x);
  return;

 lexit:
  mpfr_clear(x);
  exit(1);
}
