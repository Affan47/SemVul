check_kolmo1 (void)
{
  static const struct {
    unsigned int seed;
    int nb;
    const char *want;
  } data[] = {
    { 59618, 38208, "5"},
    { 76521, 49024, "3"},
    { 85869, 54976, "1"},
    { 99449, 63680, "1"},
    {112453, 72000, "1"}
  };

  gmp_randstate_t rs;
  mpz_t  bs, a, b, want;
  int    i, unb, vnb, nb;

  gmp_randinit_default (rs);

  mpz_inits (bs, a, b, want, NULL);

  for (i = 0; i < numberof (data); i++)
    {
      nb = data[i].nb;

      gmp_randseed_ui (rs, data[i].seed);

      mpz_urandomb (bs, rs, 32);
      unb = mpz_get_ui (bs) % nb;
      mpz_urandomb (bs, rs, 32);
      vnb = mpz_get_ui (bs) % nb;

      mpz_rrandomb (a, rs, unb);
      mpz_rrandomb (b, rs, vnb);

      mpz_set_str_or_abort (want, data[i].want, 0);

      one_test (a, b, want, -1);
    }

  mpz_clears (bs, a, b, want, NULL);
  gmp_randclear (rs);
}
