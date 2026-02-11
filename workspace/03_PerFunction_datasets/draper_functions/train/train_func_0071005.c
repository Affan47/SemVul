test_large_small (void)
{
  mpfr_t x, y, z;
  int inexact, inex2, r;

  mpfr_init2 (x, 3);
  mpfr_init2 (y, 2);
  mpfr_init2 (z, 2);

  mpfr_set_ui_2exp (x, 1, mpfr_get_emax () / 2, MPFR_RNDN);
  mpfr_set_ui_2exp (y, 1, -1, MPFR_RNDN);
  inexact = mpfr_hypot (z, x, y, MPFR_RNDN);
  if (inexact >= 0 || mpfr_cmp (x, z))
    {
      printf ("Error 1 in test_large_small%s\n",
              ext ? ", extended exponent range" : "");
      exit (1);
    }

  mpfr_mul_ui (x, x, 5, MPFR_RNDN);
  inexact = mpfr_hypot (z, x, y, MPFR_RNDN);
  if (mpfr_cmp (x, z) >= 0)
    {
      printf ("Error 2 in test_large_small%s\n",
              ext ? ", extended exponent range" : "");
      printf ("x = ");
      mpfr_out_str (stdout, 2, 0, x, MPFR_RNDN);
      printf ("\n");
      printf ("y = ");
      mpfr_out_str (stdout, 2, 0, y, MPFR_RNDN);
      printf ("\n");
      printf ("z = ");
      mpfr_out_str (stdout, 2, 0, z, MPFR_RNDN);
      printf (" (in precision 2) instead of\n    ");
      mpfr_out_str (stdout, 2, 2, x, MPFR_RNDU);
      printf ("\n");
      exit (1);
    }

  RND_LOOP(r)
    {
      mpfr_set_ui_2exp (x, 1, mpfr_get_emax () - 1, MPFR_RNDN);
      mpfr_set_ui_2exp (y, 1, mpfr_get_emin (), MPFR_RNDN);
      inexact = mpfr_hypot (z, x, y, (mpfr_rnd_t) r);
      inex2 = mpfr_add_ui (y, x, 1, (mpfr_rnd_t) r);
      if (! mpfr_equal_p (y, z) || ! SAME_SIGN (inexact, inex2))
        {
          printf ("Error 3 in test_large_small, %s%s\n",
                  mpfr_print_rnd_mode ((mpfr_rnd_t) r),
                  ext ? ", extended exponent range" : "");
          printf ("Expected ");
          mpfr_out_str (stdout, 2, 0, y, MPFR_RNDN);
          printf (", inex = %d\n", inex2);
          printf ("Got      ");
          mpfr_out_str (stdout, 2, 0, y, MPFR_RNDN);
          printf (", inex = %d\n", inexact);
          exit (1);
        }
    }

  mpfr_clear (x);
  mpfr_clear (y);
  mpfr_clear (z);
}
