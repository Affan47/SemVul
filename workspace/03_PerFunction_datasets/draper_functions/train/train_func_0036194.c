testui2 (int (*testfunc)(mpfr_ptr, unsigned long int, mpfr_srcptr, mpfr_rnd_t),
         const char *foo)
{
  mpfr_t ref1, ref3;
  unsigned int ref2;
  mpfr_t res1;
  mpfr_prec_t p1, p3;
  int i, inexa, inexd;
  mpfr_rnd_t r;

  p1 = (randlimb () % 200) + MPFR_PREC_MIN;
  p3 = (randlimb () % 200) + MPFR_PREC_MIN;

  mpfr_init2 (ref1, p1);
  mpfr_init2 (ref3, p3);
  mpfr_init2 (res1, p1);

  for (i = 0; i < SPECIAL_MAX * 2; i++)
    {
      set_special (ref3, i % SPECIAL_MAX);
      ref2 = i / SPECIAL_MAX == 0 ? 0 : randlimb ();

      inexa = testfunc (res1, ref2, ref3, MPFR_RNDA);
      r = MPFR_SIGN(res1) > 0 ? MPFR_RNDU : MPFR_RNDD;
      inexd = testfunc (ref1, ref2, ref3, r);

      if (mpfr_compare (res1, ref1) || inexa != inexd)
        {
          printf ("Error with RNDA for %s for b=%u\n", foo, ref2);
          DISP2("a=", ref3);
          printf ("inexa=%d inexd=%d\n", inexa, inexd);
          DISP("expected ", ref1); DISP2(", got ", res1);
          exit (1);
        }
    }

  mpfr_clear (ref1);
  mpfr_clear (ref3);
  mpfr_clear (res1);
}
