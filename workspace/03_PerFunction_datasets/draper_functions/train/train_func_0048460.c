destroy_fmi (fm_index *fmi) {
  int i;
  if (fmi) {
    if (fmi->bwt)
      free(fmi->bwt);
    if (fmi->idxs)
      free(fmi->idxs);
    if (fmi->rank_index) {
      for (i = 0; i <= (fmi->len+15)/16; ++i)
	if (fmi->rank_index[i])
	  free(fmi->rank_index[i]);
      free(fmi->rank_index);
    }
    if (fmi->lookup)
      free(fmi->lookup);
    free(fmi);
  }
}
