check_data (void)
{
  static const struct {
    const char     *n;
    unsigned long  want;
  } data[] = {
    { "-1", ~ (unsigned long) 0 },
    { "-12345678", ~ (unsigned long) 0 },
    { "0", 0 },
    { "1", 1 },
    { "3", 2 },
    { "5", 2 },
    { "0xFFFF", 16 },
    { "0xFFFFFFFF", 32 },
    { "0xFFFFFFFFFFFFFFFF", 64 },
    { "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 128 },
  };

  unsigned long   got;
  int    i;
  mpz_t  n;

  mpz_init (n);
  for (i = 0; i < numberof (data); i++)
    {
      mpz_set_str_or_abort (n, data[i].n, 0);
      got = mpz_popcount (n);
      if (got != data[i].want)
	{
	  printf ("mpz_popcount wrong at data[%d]\n", i);
	  printf ("   n     \"%s\"\n", data[i].n);
	  printf ("         ");   mpz_out_str (stdout, 10, n); printf ("\n");
	  printf ("         0x"); mpz_out_str (stdout, 16, n); printf ("\n");
	  printf ("   got   %lu\n", got);
	  printf ("   want  %lu\n", data[i].want);
	  abort ();
	}
    }
  mpz_clear (n);
}
