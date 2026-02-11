test_special (mpfr_prec_t p)
{
  mpfr_t x;
  int inexact;

  mpfr_init2 (x, p);

  inexact = mpfr_grandom (x, NULL, RANDS, MPFR_RNDN);
  if ((inexact & 3) == 0)
    {
      printf ("Error: mpfr_grandom() returns a zero ternary value.\n");
      exit (1);
    }
  if ((inexact & (3 << 2)) != 0)
    {
      printf ("Error: the second ternary value of mpfr_grandom(x, NULL, ...)"
              " must be 0.\n");
      exit (1);
    }

  mpfr_clear(x);
}
