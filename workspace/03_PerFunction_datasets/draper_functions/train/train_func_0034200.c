check0 (void)
{
  mpq_t y;
  mpfr_t x;
  int inexact;
  int r;


  mpfr_init (x);
  mpq_init (y);
  mpq_set_si (y, 0, 1);
  for (r = 0; r < MPFR_RND_MAX; r++)
    {
      inexact = mpfr_set_q(x, y, (mpfr_rnd_t) r);
      if (!MPFR_IS_ZERO(x) || !MPFR_IS_POS(x) || inexact)
        {
          printf("mpfr_set_q(x,0) failed for %s\n",
                 mpfr_print_rnd_mode ((mpfr_rnd_t) r));
          exit(1);
        }
    }
  mpfr_clear (x);
  mpq_clear (y);
}
