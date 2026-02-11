genhash_lookup(const struct genhash *pgenhash, const void *key,
                    void **pdata)
{
  const struct genhash_bucket *bucket;

  fc_assert_action(NULL != pgenhash,
                   genhash_default_get(NULL, pdata); return FALSE);

  bucket = genhash_bucket_lookup(pgenhash, key,
                                 genhash_val_calc(pgenhash, key));
  if (BUCKET_USED == bucket->state) {
    genhash_bucket_get(bucket, NULL, pdata);
    return TRUE;
  } else {
    genhash_default_get(NULL, pdata);
    return FALSE;
  }
}
