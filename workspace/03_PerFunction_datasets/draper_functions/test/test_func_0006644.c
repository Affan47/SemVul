check_one (mpz_srcptr n, int want)
{
  int  got;

  got = mpz_probab_prime_p (n, 25);


  if (got == 2 && want == 1)
    want = 2;

  if (got != want)
    {
      printf ("mpz_probab_prime_p\n");
      mpz_trace ("  n    ", n);
      printf    ("  got =%d", got);
      printf    ("  want=%d", want);
      abort ();
    }
}
