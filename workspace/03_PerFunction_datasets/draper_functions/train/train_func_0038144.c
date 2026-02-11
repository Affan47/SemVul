cache_get (const gchar  *root_dir,
           guint dir_mode,
           guint file_mode)
{
  Cache* cache = NULL;

  if (caches_by_root_dir == NULL)
    caches_by_root_dir = g_hash_table_new (g_str_hash, g_str_equal);
  else
    cache = g_hash_table_lookup (caches_by_root_dir, root_dir);

  if (cache != NULL)
    {
      cache->refcount += 1;
      return cache;
    }

  cache = g_new(Cache, 1);

  cache->root_dir = g_strdup(root_dir);

  cache->cache = g_hash_table_new(g_str_hash, g_str_equal);
  cache->nonexistent_cache = g_hash_table_new_full(g_str_hash, g_str_equal,
                                                   g_free, NULL);

  cache->dir_mode = dir_mode;
  cache->file_mode = file_mode;
  cache->refcount = 1;

  safe_g_hash_table_insert (caches_by_root_dir, cache->root_dir, cache);

  return cache;
}
