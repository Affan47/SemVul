ikrt_exact_bignum_sqrt(ikptr bn, ikpcb* pcb){
  ikptr fst = ref(bn, -vector_tag);
  long int limb_count = bnfst_limb_count(fst);
  long int result_limb_count = (limb_count + 1)/2;
  pcb->root0 = &bn;
  ikptr s = ik_safe_alloc(pcb,
            align(disp_bignum_data+result_limb_count*wordsize))
          + vector_tag;
  ref(s, -vector_tag) =
    (ikptr) (bignum_tag | (result_limb_count << bignum_length_shift));
  pcb->root1 = &s;
  ikptr r = ik_safe_alloc(pcb,
              align(disp_bignum_data+limb_count*wordsize))
          + vector_tag;
  ref(r, -vector_tag) =
    (ikptr) (bignum_tag | (limb_count << bignum_length_shift));
  pcb->root0 = &r;
  ikptr pair = ik_safe_alloc(pcb, pair_size) + pair_tag;
  pcb->root0 = 0;
  pcb->root1 = 0;
  mp_size_t r_actual_limbs = mpn_sqrtrem(
      (mp_limb_t*) (s+off_bignum_data),
      (mp_limb_t*) (r+off_bignum_data),
      (mp_limb_t*) (bn+off_bignum_data),
      limb_count);
  ref(pair, off_car) = normalize_bignum(result_limb_count, 0, s-vector_tag);
  if(r_actual_limbs == 0) {

    ref(pair, off_cdr) = 0;
  } else {
    ref(pair, off_cdr) = normalize_bignum(r_actual_limbs, 0, r-vector_tag);
  }
  return pair;
}
