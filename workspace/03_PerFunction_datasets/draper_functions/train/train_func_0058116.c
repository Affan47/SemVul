mpfr_zeta_part_b (mpfr_t b, mpfr_srcptr s, int n, int p, mpfr_t *tc)
{
  mpfr_t s1, d, u;
  unsigned long n2;
  int l, t;
  MPFR_GROUP_DECL (group);

  if (p == 0)
    {
      MPFR_SET_ZERO (b);
      MPFR_SET_POS (b);
      return;
    }

  n2 = n * n;
  MPFR_GROUP_INIT_3 (group, MPFR_PREC (b), s1, d, u);


  t = 2 * p - 2;
  mpfr_set (d, tc[p], MPFR_RNDN);
  for (l = 1; l < p; l++)
    {
      mpfr_add_ui (s1, s, t, MPFR_RNDN);
      mpfr_mul (d, d, s1, MPFR_RNDN);
      t = t - 1;
      mpfr_add_ui (s1, s, t, MPFR_RNDN);
      mpfr_mul (d, d, s1, MPFR_RNDN);
      t = t - 1;
      mpfr_div_ui (d, d, n2, MPFR_RNDN);
      mpfr_add (d, d, tc[p-l], MPFR_RNDN);


      if (MPFR_UNLIKELY (mpfr_cmpabs (d, tc[p-l]) > 0))
        mpfr_set (d, tc[p-l], MPFR_RNDN);
    }
  mpfr_mul (d, d, s, MPFR_RNDN);
  mpfr_add (s1, s, __gmpfr_one, MPFR_RNDN);
  mpfr_neg (s1, s1, MPFR_RNDN);
  mpfr_ui_pow (u, n, s1, MPFR_RNDN);
  mpfr_mul (b, d, u, MPFR_RNDN);

  MPFR_GROUP_CLEAR (group);
}
