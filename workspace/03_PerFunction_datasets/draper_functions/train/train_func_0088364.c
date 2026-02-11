mpfr_set_inf (mpfr_ptr x, int sign)
{
  MPFR_SET_INF(x);
  if (sign >= 0)
    MPFR_SET_POS(x);
  else
    MPFR_SET_NEG(x);
}
