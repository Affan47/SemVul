mpfr_mullow_n (mpfr_limb_ptr rp, mpfr_limb_srcptr np, mpfr_limb_srcptr mp,
               mp_size_t n)
{
  mp_size_t k;

  MPFR_ASSERTN (MPFR_MULHIGH_TAB_SIZE >= 8);
  k = MPFR_LIKELY (n < MPFR_MULHIGH_TAB_SIZE) ? mulhigh_ktab[n] : 3*(n/4);
  MPFR_ASSERTD (k == -1 || k == 0 || (2 * k >= n && k < n));
  if (k < 0)
    mpn_mul_basecase (rp, np, n, mp, n);
  else if (k == 0)
    mpfr_mullow_n_basecase (rp, np, mp, n);
  else if (n > MUL_FFT_THRESHOLD)
    mpn_mul_n (rp, np, mp, n);
  else
    {
      mp_size_t l = n - k;

      mpn_mul_n (rp, np, mp, k);
      mpfr_mullow_n (rp + n, np + k, mp, l);
      mpn_add_n (rp + k, rp + k, rp + n, l + 1);
      mpfr_mullow_n (rp + n, np, mp + k, l);
      mpn_add_n (rp + k, rp + k, rp + n, l + 1);
    }
}
