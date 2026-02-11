ikrt_fxbnmult(ikptr x, ikptr y, ikpcb* pcb){
  long int n2 = unfix(x);
  if(n2 == 0) { return 0; }
  mp_limb_t s2 = (n2>0) ? n2 : (- n2);
  ikptr fst = ref(y, -vector_tag);
  long int limb_count = bnfst_limb_count(fst);
  pcb->root0 = &y;
  ikptr r = ik_safe_alloc(pcb, align(disp_bignum_data + (limb_count+1)*wordsize));
  pcb->root0 = 0;
  mp_limb_t hi = mpn_mul_1((mp_limb_t*)(long)(r+disp_bignum_data),
                           (mp_limb_t*)(long)(y-vector_tag+disp_bignum_data),
                           limb_count,
                           s2);
  ref(r, disp_bignum_data + limb_count * wordsize) = (ikptr)hi;
  long int sign =
    ((n2 > 0) ?
     (bignum_sign_mask & (long int)fst) :
     ((1 << bignum_sign_shift) - (bignum_sign_mask&(long int)fst)));
  return normalize_bignum(limb_count+1, sign, r);
}
