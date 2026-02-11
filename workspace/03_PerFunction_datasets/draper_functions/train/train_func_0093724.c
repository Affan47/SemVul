make_fmi(const char *str, int len) {
  int *idxs, i;
  fm_index *fmi;
  idxs = histsort(str, len);


  fmi = calloc(1, sizeof(fm_index));
  fmi->idxs = malloc((1 + (len / 32)) * sizeof(int));

  for (i = 0; i < (1+(len / 32)); ++i)
    fmi->idxs[i] = idxs[32 * i];
  fmi->bwt = malloc((len+3)/4);
  fmi->len = len;
  fmi->endloc = sprintcbwt(str, idxs, len, fmi->bwt);
  free(idxs);
  fmi->lookup = lookup_table();
  fmi->rank_index = seq_index(fmi->bwt, len, 16, fmi->lookup);
  fmi->C[0] = 1;
  fmi->C[1] = 1         + fmi->rank_index[(len+15)/16][0];
  fmi->C[2] = fmi->C[1] + fmi->rank_index[(len+15)/16][1];
  fmi->C[3] = fmi->C[2] + fmi->rank_index[(len+15)/16][2];
  fmi->C[4] = fmi->C[3] + fmi->rank_index[(len+15)/16][3];
  return fmi;
}
