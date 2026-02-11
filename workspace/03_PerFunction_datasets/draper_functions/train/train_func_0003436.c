mpfr_divhigh_n (mpfr_limb_ptr qp, mpfr_limb_ptr np, mpfr_limb_ptr dp,
                mp_size_t n)
{
  mp_size_t k, l;
  mp_limb_t qh, cy;
  mpfr_limb_ptr tp;
  MPFR_TMP_DECL(marker);

  MPFR_ASSERTN (MPFR_MULHIGH_TAB_SIZE >= 15);
  k = MPFR_LIKELY (n < MPFR_DIVHIGH_TAB_SIZE) ? divhigh_ktab[n] : 2*(n/3);

  if (k == 0)
#if defined(WANT_GMP_INTERNALS) && defined(HAVE___GMPN_SBPI1_DIVAPPR_Q)
  {
    mpfr_pi1_t dinv2;
    invert_pi1 (dinv2, dp[n - 1], dp[n - 2]);
    return __gmpn_sbpi1_divappr_q (qp, np, n + n, dp, n, dinv2.inv32);
  }
#else
    return mpfr_divhigh_n_basecase (qp, np, dp, n);
#endif
  else if (k == n)


    return mpn_divrem (qp, 0, np, 2 * n, dp, n);

  MPFR_ASSERTD ((n+4)/2 <= k && k < n);
  MPFR_TMP_MARK (marker);
  l = n - k;


  qh = mpn_divrem (qp + l, 0, np + 2 * l, 2 * k, dp + l, k);


  tp = MPFR_TMP_LIMBS_ALLOC (2 * l);
  mpfr_mulhigh_n (tp, qp + k, dp, l);

  cy = mpn_sub_n (np + n, np + n, tp + l, l);
  if (qh)
    cy += mpn_sub_n (np + n, np + n, dp, l);
  while (cy > 0)
    {
      qh -= mpn_sub_1 (qp + l, qp + l, k, MPFR_LIMB_ONE);
      cy -= mpn_add_n (np + l, np + l, dp, n);
    }


  cy = mpfr_divhigh_n (qp, np + k, dp + k, l);
  qh += mpn_add_1 (qp + l, qp + l, k, cy);
  MPFR_TMP_FREE(marker);

  return qh;
}
