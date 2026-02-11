check_one (mpz_ptr x, mpz_ptr y, int want_cmp, int want_cmpabs)
{
  int  got;

  got = mpz_cmp (x, y);
  if ((   got <  0) != (want_cmp <  0)
      || (got == 0) != (want_cmp == 0)
      || (got >  0) != (want_cmp >  0))
    {
      printf ("mpz_cmp got %d want %d\n", got, want_cmp);
      mpz_trace ("x", x);
      mpz_trace ("y", y);
      abort ();
    }

  got = mpz_cmpabs (x, y);
  if ((   got <  0) != (want_cmpabs <  0)
      || (got == 0) != (want_cmpabs == 0)
      || (got >  0) != (want_cmpabs >  0))
    {
      printf ("mpz_cmpabs got %d want %d\n", got, want_cmpabs);
      mpz_trace ("x", x);
      mpz_trace ("y", y);
      abort ();
    }
}
