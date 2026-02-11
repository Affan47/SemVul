assign_cdna_forward (int ncdna, struct Pair_T *pairs, int npairs, bool revcompp, int starti) {
  struct Pair_T *pair;
  int i, nexti, j = 0, codon;

  i = starti;
  while (i < npairs && pairs[i].cdna == ' ') {
    i++;
  }
  while (j < ncdna) {
    pair = &(pairs[i]);
    codon = pair->aa_e = get_codon_forward(&nexti,pairs,npairs,i,revcompp);
    debug2(Pair_dump_one(pair,true));
    debug2(printf(" marked with amino acid %c\n",pair->aa_e));
    i = nexti;
    j += 3;
  }
  return codon;
}
