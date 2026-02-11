check_rand (void)
{
  unsigned long      max_prec = 15;
  unsigned long      min_prec = __GMPF_BITS_TO_PREC (1);
  gmp_randstate_ptr  rands = RANDS;
  unsigned long      x, prec;
  mpf_t              r, s;
  int                i;

  mpf_init (r);
  mpf_init (s);
  refmpf_set_prec_limbs (s, 2*max_prec+10);

  for (i = 0; i < 50; i++)
    {

      do {
        x = gmp_urandomb_ui (rands,
                             gmp_urandomm_ui (rands, BITS_PER_ULONG) + 1);
      } while (x == 0);


      prec = gmp_urandomm_ui (rands, max_prec-min_prec) + min_prec;
      refmpf_set_prec_limbs (r, prec);

      mpf_sqrt_ui (r, x);
      MPF_CHECK_FORMAT (r);


      if (SIZ(r) != prec)
        {
          printf ("mpf_sqrt_ui result not enough result limbs\n");
          printf    ("  x=%lu\n", x);
          printf    ("  want prec=%lu\n", prec);
          mpf_trace ("  r", r);
          printf    ("  r size %ld\n", (long) SIZ(r));
          printf    ("  r prec %ld\n", (long) PREC(r));
          abort ();
        }


      mpf_mul (s, r, r);
      if (! (mpf_cmp_ui (s, x) <= 0))
        {
          printf    ("mpf_sqrt_ui result too big\n");
          printf    ("  x=%lu\n", x);
          printf    ("  want prec=%lu\n", prec);
          mpf_trace ("  r", r);
          mpf_trace ("  s", s);
          abort ();
        }


      refmpf_add_ulp (r);
      mpf_mul (s, r, r);
      if (! (mpf_cmp_ui (s, x) > 0))
        {
          printf    ("mpf_sqrt_ui result too small\n");
          printf    ("  x=%lu\n", x);
          printf    ("  want prec=%lu\n", prec);
          mpf_trace ("  r+ulp", r);
          mpf_trace ("  s", s);
          abort ();
        }
    }

  mpf_clear (r);
  mpf_clear (s);
}
