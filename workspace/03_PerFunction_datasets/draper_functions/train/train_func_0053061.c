copysign_variant (mpfr_ptr z, mpfr_srcptr x, mpfr_srcptr y,
                  mpfr_rnd_t rnd_mode, int k)
{
  mpfr_clear_flags ();
  switch (k)
    {
    case 0:
      mpfr_copysign (z, x, y, MPFR_RNDN);
      return;
    case 1:
      (mpfr_copysign) (z, x, y, MPFR_RNDN);
      return;
    case 2:
      mpfr_setsign (z, x, mpfr_signbit (y), MPFR_RNDN);
      return;
    case 3:
      mpfr_setsign (z, x, (mpfr_signbit) (y), MPFR_RNDN);
      return;
    case 4:
      (mpfr_setsign) (z, x, mpfr_signbit (y), MPFR_RNDN);
      return;
    case 5:
      (mpfr_setsign) (z, x, (mpfr_signbit) (y), MPFR_RNDN);
      return;
    }
}
