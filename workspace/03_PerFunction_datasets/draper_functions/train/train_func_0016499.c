mpc_cmp_si_si (mpc_srcptr a, long int b, long int c)
{
  int cmp_re, cmp_im;

  cmp_re = mpfr_cmp_si (mpc_realref(a), b);
  cmp_im = mpfr_cmp_si (mpc_imagref(a), c);

  return MPC_INEX(cmp_re, cmp_im);
}
