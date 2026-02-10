bug20080721 (void)
{
  mpfr_t x, y, z, t[2];
  int inex;
  int rnd;
  int err = 0;


  mpfr_inits2 (4913, x, y, (mpfr_ptr) 0);
  mpfr_inits2 (8, z, t[0], t[1], (mpfr_ptr) 0);
  mpfr_set_si (x, -1, MPFR_RNDN);
  mpfr_nextbelow (x);
  mpfr_set_ui_2exp (y, 1, mpfr_get_prec (y) - 1, MPFR_RNDN);
  inex = mpfr_add_ui (y, y, 1, MPFR_RNDN);
  MPFR_ASSERTN (inex == 0);
  mpfr_set_str_binary (t[0], "-0.10101101e2");
  mpfr_set_str_binary (t[1], "-0.10101110e2");
  RND_LOOP (rnd)
    {
      int i, inex0;

      i = (rnd == MPFR_RNDN || rnd == MPFR_RNDD || rnd == MPFR_RNDA);
      inex0 = i ? -1 : 1;
      mpfr_clear_flags ();
      inex = mpfr_pow (z, x, y, (mpfr_rnd_t) rnd);
      if (__gmpfr_flags != MPFR_FLAGS_INEXACT || ! SAME_SIGN (inex, inex0)
          || MPFR_IS_NAN (z) || mpfr_cmp (z, t[i]) != 0)
        {
          unsigned int flags = __gmpfr_flags;

          printf ("Error in bug20080721 with %s\n",
                  mpfr_print_rnd_mode ((mpfr_rnd_t) rnd));
          printf ("expected ");
          mpfr_out_str (stdout, 2, 0, t[i], MPFR_RNDN);
          printf (", inex = %d, flags = %u\n", inex0,
                  (unsigned int) MPFR_FLAGS_INEXACT);
          printf ("got      ");
          mpfr_out_str (stdout, 2, 0, z, MPFR_RNDN);
          printf (", inex = %d, flags = %u\n", inex, flags);
          err = 1;
        }
    }
  mpfr_clears (x, y, z, t[0], t[1], (mpfr_ptr) 0);
  if (err)
    exit (1);
}
