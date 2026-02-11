check_onebit (void)
{
  static const unsigned long data[] = {
    1, 32, 52, 53, 54, 63, 64, 65, 128, 256, 511, 512, 513
  };
  mpz_t   z;
  double  got, want;
  long    got_exp, want_exp;
  int     i;

  mpz_init (z);

  for (i = 0; i < numberof (data); i++)
    {
      mpz_set_ui (z, 1L);
      mpz_mul_2exp (z, z, data[i]);
      want = 0.5;
      want_exp = data[i] + 1;
      got = mpz_get_d_2exp (&got_exp, z);
      if (got != want || got_exp != want_exp)
        {
          printf    ("mpz_get_d_2exp wrong on 2**%ld\n", data[i]);
          mpz_trace ("   z    ", z);
          d_trace   ("   want ", want);
          d_trace   ("   got  ", got);
          printf    ("   want exp %ld\n", want_exp);
          printf    ("   got exp  %ld\n", got_exp);
          abort();
        }

      mpz_set_si (z, -1L);
      mpz_mul_2exp (z, z, data[i]);
      want = -0.5;
      want_exp = data[i] + 1;
      got = mpz_get_d_2exp (&got_exp, z);
      if (got != want || got_exp != want_exp)
        {
          printf    ("mpz_get_d_2exp wrong on -2**%ld\n", data[i]);
          mpz_trace ("   z    ", z);
          d_trace   ("   want ", want);
          d_trace   ("   got  ", got);
          printf    ("   want exp %ld\n", want_exp);
          printf    ("   got exp  %ld\n", got_exp);
          abort();
        }
    }
  mpz_clear (z);
}
