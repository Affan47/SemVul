genhashs_are_equal_full(const struct genhash *pgenhash1,
                             const struct genhash *pgenhash2,
                             genhash_comp_fn_t data_comp_func)
{
  const struct genhash_bucket *bucket1, *max1, *bucket2;


  if (pgenhash1 == pgenhash2) {
    return TRUE;
  } else if (NULL == pgenhash1 || NULL == pgenhash2) {
    return FALSE;
  }


  if (pgenhash1->num_entries != pgenhash2->num_entries


      || pgenhash1->key_val_func != pgenhash2->key_val_func
      || pgenhash1->key_comp_func != pgenhash2->key_comp_func) {
    return FALSE;
  }

  if (NULL == data_comp_func) {

    data_comp_func = genhash_ptr_comp_func;
  }


  max1 = pgenhash1->buckets + pgenhash1->num_buckets;
  for (bucket1 = pgenhash1->buckets; bucket1 < max1; bucket1++) {
    if (BUCKET_USED == bucket1->state) {
      bucket2 = genhash_bucket_lookup(pgenhash2, bucket1->key,
                                      genhash_val_calc(pgenhash2,
                                                       bucket1->key));
      if (BUCKET_USED != bucket2->state
          || !data_comp_func(bucket1->data, bucket2->data)) {
        return FALSE;
      }
    }
  }

  return TRUE;
}
