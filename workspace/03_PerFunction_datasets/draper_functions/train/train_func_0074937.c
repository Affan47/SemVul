check53 (const char *xs, const char *sin_xs, mpfr_rnd_t rnd_mode)
{
  mpfr_t xx, s;

  mpfr_init2 (xx, 53);
  mpfr_init2 (s, 53);
  mpfr_set_str1 (xx, xs);
  test_sin (s, xx, rnd_mode);
  if (mpfr_cmp_str1 (s, sin_xs))
    {
      printf ("mpfr_sin failed for x=%s, rnd=%s\n",
              xs, mpfr_print_rnd_mode (rnd_mode));
      printf ("mpfr_sin gives sin(x)=");
      mpfr_out_str (stdout, 10, 0, s, MPFR_RNDN);
      printf (", expected %s\n", sin_xs);
      exit (1);
    }
  mpfr_clear (xx);
  mpfr_clear (s);
}
