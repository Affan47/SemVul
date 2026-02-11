check_data (void)
{
  static const struct {
    int         base;
    const char  *num;
    const char  *den;
    const char  *want;
  } data[] = {
    { 10, "0", "1", "0" },
    { 10, "1", "1", "1" },

    { 16, "ffffffff", "1", "ffffffff" },
    { 16, "ffffffffffffffff", "1", "ffffffffffffffff" },

    { 16, "1", "ffffffff", "1/ffffffff" },
    { 16, "1", "ffffffffffffffff", "1/ffffffffffffffff" },
    { 16, "1", "10000000000000003", "1/10000000000000003" },

    { 10, "12345678901234567890", "9876543210987654323",
      "12345678901234567890/9876543210987654323" },
  };

  mpq_t  q;
  int    i;

  mpq_init (q);
  for (i = 0; i < numberof (data); i++)
    {
      mpz_set_str_or_abort (mpq_numref(q), data[i].num, data[i].base);
      mpz_set_str_or_abort (mpq_denref(q), data[i].den, data[i].base);
      check_all (q, data[i].base, data[i].want);
    }
  mpq_clear (q);
}
