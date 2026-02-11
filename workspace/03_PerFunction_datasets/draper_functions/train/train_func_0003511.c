grl_tracker_source_cache_new (gsize size)
{
  GrlTrackerCache *cache;

  g_return_val_if_fail (size > 0, NULL);

  cache = g_slice_new0 (GrlTrackerCache);

  if (!cache)
    return NULL;

  cache->size_limit   = size;
  cache->id_table     = g_hash_table_new (g_direct_hash, g_direct_equal);
  cache->source_table = g_hash_table_new (g_direct_hash, g_direct_equal);

  return cache;
}
