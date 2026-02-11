u_to_number(unsigned long n, ikpcb* pcb) {
  unsigned long mxn = ((unsigned long)-1)>>(fx_shift+1);
  if (n <= mxn) {
    return fix(n);
  }
  ikptr bn = ik_safe_alloc(pcb, align(wordsize+disp_bignum_data));
  ref(bn, 0) = (ikptr)(bignum_tag | (1 << bignum_length_shift));
  ref(bn, disp_bignum_data) = (ikptr)n;
  return bn+vector_tag;
}
