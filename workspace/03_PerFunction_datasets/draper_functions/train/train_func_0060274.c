dfa_finalize(dfa_t *pdfa)
{
  int j;
  int next_bin = aux_count;
  int last_bin = aux_count + DFA_BINS - 1;
  while (next_bin + 1 != last_bin) {
    for (j = aux_count + 1; j <= last_bin; j += 2) {
      if (j+1 == next_bin)
        copy_dfa(&aux_dfa[next_bin % DFA_BINS], &aux_dfa[j % DFA_BINS]);
      else
        sync_product(&aux_dfa[next_bin % DFA_BINS],
                     &aux_dfa[j % DFA_BINS],
                     &aux_dfa[(j+1) % DFA_BINS]);
      next_bin++;
    }
    last_bin = next_bin - 1;
    aux_count--;
    next_bin = aux_count;
  }
  copy_dfa(pdfa, &aux_dfa[last_bin % DFA_BINS]);

  compactify_att(pdfa);
}
