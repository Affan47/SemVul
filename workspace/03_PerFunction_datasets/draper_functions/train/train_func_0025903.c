main (void)
{
  mpfr_t ip, fp;
  int ni, nf1, nf2;

  tests_start_mpfr ();

  special ();

  mpfr_init2 (ip, PIP);
  mpfr_init2 (fp, PFP);

  for (ni = -1; ni < PIP; ni++)
    {
      if (ni <= 0)
        {
          mpfr_set_si (ip, ni, MPFR_RNDN);
          mpfr_add_ui (ip, ip, 1, MPFR_RNDN);
        }
      else
        {
          mpfr_set_ui (ip, 1, MPFR_RNDN);
          mpfr_mul_2ui (ip, ip, ni, MPFR_RNDN);
          mpfr_add_ui (ip, ip, 1, MPFR_RNDN);
        }

      mpfr_set_ui (fp, 0, MPFR_RNDN);
      check1 (ip, fp);

      for (nf1 = 1; nf1 < PFP; nf1++)
        {
          mpfr_set_ui (fp, 1, MPFR_RNDN);
          mpfr_div_2ui (fp, fp, nf1, MPFR_RNDN);
          check1 (ip, fp);
          nf2 = 1 + (randlimb () % (PFP - 1));
          mpfr_set_ui (fp, 1, MPFR_RNDN);
          mpfr_div_2ui (fp, fp, nf2, MPFR_RNDN);
          mpfr_add_ui (fp, fp, 1, MPFR_RNDN);
          mpfr_div_2ui (fp, fp, nf1, MPFR_RNDN);
          check1 (ip, fp);
        }
    }

  mpfr_set_ui (ip, 1, MPFR_RNDN);
  mpfr_div_ui (ip, ip, 0, MPFR_RNDN);
  mpfr_set_ui (fp, 0, MPFR_RNDN);
  check1 (ip, fp);

  mpfr_clear (ip);
  mpfr_clear (fp);

  bug20090918 ();

  test_generic (2, 1000, 10);

  tests_end_mpfr ();
  return 0;
}
