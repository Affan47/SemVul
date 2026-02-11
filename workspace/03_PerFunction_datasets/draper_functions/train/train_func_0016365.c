bug20080223 (void)
{
  mpfr_t a, exp, answer;

  mpfr_init2 (a, 53);
  mpfr_init2 (exp, 53);
  mpfr_init2 (answer, 53);

  mpfr_set_si (exp, -1073741824, MPFR_RNDN);

  mpfr_set_str (a, "1.999999999", 10, MPFR_RNDN);

  mpfr_pow (answer, a, exp, MPFR_RNDN);
  mpfr_set_str_binary (a, "0.110110101111011001110000111111100011101000111011101E-1073741823");
  MPFR_ASSERTN(mpfr_cmp0 (answer, a) == 0);

  mpfr_clear (a);
  mpfr_clear (exp);
  mpfr_clear (answer);
}
