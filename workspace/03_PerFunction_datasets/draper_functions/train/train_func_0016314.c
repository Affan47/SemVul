mark_cdna_backward_strict (struct Pair_T *pairs, int npairs, bool revcompp, int starti, int endi) {
  struct Pair_T *pair;
  int i, nexti, ncdna, codon = ' ';

  debug2(printf("mark_cdna_backward called with pairs #%d..%d\n",starti,endi));

  i = starti;


  pair = &(pairs[i]);
  while (i > endi && pair->aaphase_g != 0) {
    i--;
    pair = &(pairs[i]);
  }

  while (i >= 0 && codon != '*') {
    pair = &(pairs[i]);
    ncdna = count_cdna_backward_strict(&nexti,pairs,npairs,i,endi);
    if (ncdna == 3) {
      codon = assign_cdna_backward(ncdna,pairs,npairs,revcompp,i);
    }
    i = nexti;
  }

  if (codon != '*') {
    terminate_cdna_backward(pairs,npairs,revcompp,i);
  }

  return;
}
