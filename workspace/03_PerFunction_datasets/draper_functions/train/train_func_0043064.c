coverage_01032011 (void)
{
  mpfr_t val, cval, sval, svalf;
  int status_f, status;

  mpfr_init2 (val, MPFR_PREC_MIN);
  mpfr_init2 (cval, MPFR_PREC_MIN);
  mpfr_init2 (sval, MPFR_PREC_MIN);
  mpfr_init2 (svalf, MPFR_PREC_MIN);

  mpfr_set_str1 (val, "-0.7");

  status_f = mpfr_sincos_fast (svalf, NULL, val, MPFR_RNDN);
  status = mpfr_sin_cos (sval, cval, val, MPFR_RNDN);
  if (! mpfr_equal_p (svalf, sval) || SIGN (status_f) != SIGN (status))
    {
      printf ("mpfr_sincos_fast differ from mpfr_sin_cos result:\n"
              " sin fast is ");
      mpfr_dump (svalf);
      printf (" sin is ");
      mpfr_dump (sval);
      printf ("status_f = %d, status = %d\n", status_f, status);
      exit (1);
    }

  mpfr_clears(val, cval, sval, svalf, (mpfr_ptr) 0);
}
