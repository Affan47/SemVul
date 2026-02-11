mpfr_gamma_2_minus_x_exact (mpfr_srcptr x)
{


  return (MPFR_GET_EXP(x) <= 1) ? MPFR_PREC(x) + 2 - MPFR_GET_EXP(x)
    : ((MPFR_GET_EXP(x) <= MPFR_PREC(x) + 1) ? MPFR_PREC(x) + 1
       : MPFR_GET_EXP(x) - 1);
}
