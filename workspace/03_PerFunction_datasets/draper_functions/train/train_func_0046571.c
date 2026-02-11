check_sign (void)
{
  mpfr_t a, b;

  mpfr_init2 (a, 53);
  mpfr_init2 (b, 53);
  mpfr_set_si (a, -1, MPFR_RNDN);
  mpfr_set_ui (b, 2, MPFR_RNDN);
  test_mul(a, b, b, MPFR_RNDN);
  if (mpfr_cmp_ui (a, 4) )
    {
      printf ("2.0*2.0 gives \n");
      mpfr_out_str(stdout, 10, 0, a, MPFR_RNDN);
      putchar('\n');
      exit (1);
    }
  mpfr_clear(a); mpfr_clear(b);
}
