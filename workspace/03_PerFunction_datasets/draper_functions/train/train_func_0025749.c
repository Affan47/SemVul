xcsv_ofield_add(char* key, char* val, char* pfc, int options)
{
  field_map_t* fmp = (field_map_t*) xcalloc(sizeof(*fmp), 1);
  struct xt_mapping* xm = in_word_set(key, strlen(key));

  fmp->key = key;
  fmp->hashed_key = xm ? xm->xt_token : -1;
  fmp->val = val;
  fmp->printfc = pfc;
  fmp->options = options;

  ENQUEUE_TAIL(xcsv_file.ofield, &fmp->Q);
  xcsv_file.ofield_ct++;
}
