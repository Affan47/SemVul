terminate_cdna_forward (struct Pair_T *pairs, int npairs, bool revcompp, int starti) {
  struct Pair_T *pair;
  int i, nexti;
  char lastcodon = ' ';

  i = starti;
  while (i < npairs && pairs[i].cdna == ' ') {
    i++;
  }
  while (i <= npairs-3 && lastcodon != '*') {
    pair = &(pairs[i]);
    lastcodon = pair->aa_e = get_codon_forward(&nexti,pairs,npairs,i,revcompp);
    debug2(Pair_dump_one(pair,true));
    debug2(printf(" marked with amino acid %c\n",pair->aa_e));
    i = nexti;
  }
  return;
}
