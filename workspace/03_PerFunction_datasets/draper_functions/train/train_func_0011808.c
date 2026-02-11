ght_set_bounded_buckets(ght_hash_table_t *p_ht, unsigned int limit, ght_fn_bucket_free_callback_t fn)
{
  p_ht->bucket_limit = limit;
  p_ht->fn_bucket_free = fn;

  if (limit > 0 && fn == NULL)
    {
      fprintf(stderr, "ght_set_bounded_buckets: The bucket callback function is NULL but the limit is %d\n", limit);
    }
}
