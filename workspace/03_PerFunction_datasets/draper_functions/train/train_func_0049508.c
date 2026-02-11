bug20081028 (void)
{
  mpfr_t x;
  const char *s = "0.10000000000000000000000000000001E1";

  mpfr_init2 (x, 32);
  mpfr_set_str (x, "1.00000000000000000006", 10, MPFR_RNDU);
  if (! mpfr_greater_p (x, __gmpfr_one))
    {
      printf ("Error in bug20081028:\nExpected %s\nGot      ", s);
      mpfr_dump (x);
      exit (1);
    }
  mpfr_clear (x);
}
