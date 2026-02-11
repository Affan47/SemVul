check_data (void)
{
#if GMP_NUMB_BITS <= BITS_PER_ULONG
#define ENTRY(n)   { n, { n, 0 } }
#else
#define ENTRY(n)   { n, { (n) & GMP_NUMB_MASK, (n) >> GMP_NUMB_BITS } }
#endif

  static const struct {
    long       n;
    mp_size_t  want_size;
    mp_limb_t  want_data[2];
  } data[] = {

    {  0L,  0 },
    {  1L,  1, { 1 } },
    { -1L, -1, { 1 } },

#if GMP_NUMB_BITS >= BITS_PER_ULONG
    { LONG_MAX,  1, { LONG_MAX, 0 } },
    { -LONG_MAX,  -1, { LONG_MAX, 0 } },
    { LONG_HIGHBIT,  -1, { ULONG_HIGHBIT, 0 } },
#else
    { LONG_MAX,  2, { LONG_MAX & GMP_NUMB_MASK, LONG_MAX >> GMP_NUMB_BITS } },
    { -LONG_MAX,  -2, { LONG_MAX & GMP_NUMB_MASK, LONG_MAX >> GMP_NUMB_BITS }},
    { LONG_HIGHBIT,  -2, { 0, ULONG_HIGHBIT >> GMP_NUMB_BITS } },
#endif
  };

  mpz_t  n;
  int    i;

  for (i = 0; i < numberof (data); i++)
    {
      mpz_init (n);
      mpz_set_si (n, data[i].n);
      MPZ_CHECK_FORMAT (n);
      if (n->_mp_size != data[i].want_size
          || refmpn_cmp_allowzero (n->_mp_d, data[i].want_data,
                                   ABS (data[i].want_size)) != 0)
        {
          printf ("mpz_set_si wrong on data[%d]\n", i);
          abort();
        }
      mpz_clear (n);

      mpz_init_set_si (n, data[i].n);
      MPZ_CHECK_FORMAT (n);
      if (n->_mp_size != data[i].want_size
          || refmpn_cmp_allowzero (n->_mp_d, data[i].want_data,
                                   ABS (data[i].want_size)) != 0)
        {
          printf ("mpz_init_set_si wrong on data[%d]\n", i);
          abort();
        }
      mpz_clear (n);
    }
}
