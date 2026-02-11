bp_bulk_updates(bp_db_t* tree,
                    const uint64_t count,
                    const char** keys,
                    const char** values,
                    bp_update_cb update_cb,
                    void* arg) {
  int ret;
  bp_key_t* bkeys;
  bp_value_t* bvalues;
  uint64_t i;


  bkeys = malloc(sizeof(*bkeys) * count);
  if (bkeys == NULL) return BP_EALLOC;

  bvalues = malloc(sizeof(*bvalues) * count);
  if (bvalues == NULL) {
    free(bkeys);
    return BP_EALLOC;
  }


  for (i = 0; i < count; i++) {
    BP__STOVAL(keys[i], bkeys[i]);
    BP__STOVAL(values[i], bvalues[i]);
  }

  ret = bp_bulk_update(tree,
                       count,
                       (const bp_key_t**) &bkeys,
                       (const bp_value_t**) &bvalues,
                       update_cb,
                       arg);

  free(bkeys);
  free(bvalues);

  return ret;
}
