mpfr_gamma_1_minus_x_exact (mpfr_srcptr x)
{
  if (MPFR_IS_POS(x))
    return MPFR_PREC(x) - MPFR_GET_EXP(x);
  else if (MPFR_GET_EXP(x) <= 0)
    return MPFR_PREC(x) + 1 - MPFR_GET_EXP(x);
  else if (MPFR_PREC(x) >= MPFR_GET_EXP(x))
    return MPFR_PREC(x) + 1;
  else
    return MPFR_GET_EXP(x);
}
