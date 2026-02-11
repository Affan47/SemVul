check_min(void)
{
  mpfr_t xx, yy, zz;

  mpfr_init2(xx, 4);
  mpfr_init2(yy, 4);
  mpfr_init2(zz, 3);
  mpfr_set_str1(xx, "0.9375");
  mpfr_mul_2si(xx, xx, MPFR_EMIN_DEFAULT/2, MPFR_RNDN);
  mpfr_set_str1(yy, "0.9375");
  mpfr_mul_2si(yy, yy, MPFR_EMIN_DEFAULT - MPFR_EMIN_DEFAULT/2 - 1, MPFR_RNDN);
  test_mul(zz, xx, yy, MPFR_RNDD);
  if (mpfr_sgn(zz) != 0)
    {
      printf("check_min failed: got ");
      mpfr_out_str(stdout, 2, 0, zz, MPFR_RNDZ);
      printf(" instead of 0\n");
      exit(1);
    }

  test_mul(zz, xx, yy, MPFR_RNDU);
  mpfr_set_str1 (xx, "0.5");
  mpfr_mul_2si(xx, xx, MPFR_EMIN_DEFAULT, MPFR_RNDN);
  if (mpfr_sgn(xx) <= 0)
    {
      printf("check_min failed (internal error)\n");
      exit(1);
    }
  if (mpfr_cmp(xx, zz) != 0)
    {
      printf("check_min failed: got ");
      mpfr_out_str(stdout, 2, 0, zz, MPFR_RNDZ);
      printf(" instead of ");
      mpfr_out_str(stdout, 2, 0, xx, MPFR_RNDZ);
      printf("\n");
      exit(1);
    }

  mpfr_clear(xx);
  mpfr_clear(yy);
  mpfr_clear(zz);
}
