submul (mp_ptr rp, mp_size_t rn,
	mp_srcptr ap, mp_size_t an, mp_srcptr bp, mp_size_t bn)
{
  mp_ptr tp;
  TMP_DECL;

  ASSERT (bn > 0);
  ASSERT (an >= bn);
  ASSERT (rn >= an);
  ASSERT (an + bn <= rn + 1);

  TMP_MARK;
  tp = TMP_ALLOC_LIMBS (an + bn);

  mpn_mul (tp, ap, an, bp, bn);
  if (an + bn > rn)
    {
      ASSERT (tp[rn] == 0);
      bn--;
    }
  ASSERT_NOCARRY (mpn_sub (rp, rp, rn, tp, an + bn));
  TMP_FREE;

  while (rn > an && (rp[rn-1] == 0))
    rn--;

  return rn;
}
