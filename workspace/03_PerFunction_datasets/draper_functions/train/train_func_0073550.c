ref_mulmod_bnm1 (mp_ptr rp, mp_size_t rn, mp_srcptr ap, mp_size_t an, mp_srcptr bp, mp_size_t bn)
{
  mp_limb_t cy;

  ASSERT (0 < an && an <= rn);
  ASSERT (0 < bn && bn <= rn);

  if (an >= bn)
    refmpn_mul (rp, ap, an, bp, bn);
  else
    refmpn_mul (rp, bp, bn, ap, an);
  an += bn;
  if (an > rn) {
    cy = mpn_add (rp, rp, rn, rp + rn, an - rn);


    MPN_INCR_U (rp, rn, cy);
  }
}
