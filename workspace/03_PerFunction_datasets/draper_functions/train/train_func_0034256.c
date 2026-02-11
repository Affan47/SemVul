mixed (void)
{
  int n1;
  int n2;
  int i = 121;
#ifndef NPRINTF_L
  long double d = 1. / 31.;
#endif
  mpf_t mpf;
  mpq_t mpq;
  mpz_t mpz;
  mpfr_t x;
  mpfr_rnd_t rnd;

  mpf_init (mpf);
  mpf_set_ui (mpf, 40);
  mpf_div_ui (mpf, mpf, 31);
  mpq_init (mpq);
  mpq_set_ui (mpq, 123456, 4567890);
  mpz_init (mpz);
  mpz_fib_ui (mpz, 64);
  mpfr_init (x);
  mpfr_set_str (x, "-12345678.875", 10, MPFR_RNDN);
  rnd = MPFR_RNDD;

  check_vsprintf ("121%", "%i%%", i);
  check_vsprintf ("121% -1.2345678875E+07", "%i%% %RNE", i, x);
  check_vsprintf ("121, -12345679", "%i, %.0Rf", i, x);
  check_vsprintf ("10610209857723, -1.2345678875e+07", "%Zi, %R*e", mpz, rnd,
                  x);
  check_vsprintf ("-12345678.9, 121", "%.1Rf, %i", x, i);
  check_vsprintf ("-12345678, 1e240/45b352", "%.0R*f, %Qx", MPFR_RNDZ, x, mpq);
  n1 = check_vsprintf ("121, -12345678.875000000000, 1.290323", "%i, %.*Rf, %Ff%n",
                       i, 12, x, mpf, &n2);
  if (n1 != n2)
    {
      printf ("error in number of characters written by mpfr_vsprintf\n");
      printf ("expected: %d\n", n2);
      printf ("     got: %d\n", n1);
      exit (1);
    }

#ifndef NPRINTF_L
  check_vsprintf ("00000010610209857723, -1.2345678875e+07, 0.032258",
                  "%.*Zi, %R*e, %Lf", 20, mpz, rnd, x, d);
#endif

  mpf_clear (mpf);
  mpq_clear (mpq);
  mpz_clear (mpz);
  mpfr_clear (x);
  return 0;
}
