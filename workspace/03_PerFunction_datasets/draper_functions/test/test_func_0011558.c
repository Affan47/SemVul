mpfr_mulhigh_n_basecase (mpfr_limb_ptr rp, mpfr_limb_srcptr up,
                         mpfr_limb_srcptr vp, mp_size_t n)
{
  mp_size_t i;

  rp += n - 1;
  umul_ppmm (rp[1], rp[0], up[n-1], vp[0]);

  for (i = 1 ; i < n ; i++)

    rp[i + 1] = mpn_addmul_1 (rp, up + (n - i - 1), i + 1, vp[i]);

}
