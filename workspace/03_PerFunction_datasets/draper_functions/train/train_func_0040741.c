est_idx_out(ESTIDX *idx, const char *word, int wsiz){
  int i, err;
  assert(idx && word && wsiz >= 0);
  err = FALSE;
  for(i = 0; i < idx->dnum; i++){
    if(!vlout(idx->dbs[i], word, wsiz) && dpecode != DP_ENOITEM) err = TRUE;
  }
  return err ? FALSE : TRUE;
}
