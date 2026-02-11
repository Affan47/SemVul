check0 (void)
{
  mpz_t y;
  mpfr_t x;
  int inexact, r;
  mpfr_exp_t e;


  mpfr_init (x);
  mpz_init (y);
  mpz_set_si (y, 0);
  for (r = 0; r < MPFR_RND_MAX; r++)
    {
      e = randexp ();
      inexact = mpfr_set_z_2exp (x, y, e, (mpfr_rnd_t) r);
      if (!MPFR_IS_ZERO(x) || !MPFR_IS_POS(x) || inexact)
        {
          printf ("mpfr_set_z_2exp(x,0,e) failed for e=");
          if (e < LONG_MIN)
            printf ("(<LONG_MIN)");
          else if (e > LONG_MAX)
            printf ("(>LONG_MAX)");
          else
            printf ("%ld", (long) e);
          printf (", rnd=%s\n", mpfr_print_rnd_mode ((mpfr_rnd_t) r));
          exit (1);
        }
    }
  mpfr_clear(x);
  mpz_clear(y);
}
