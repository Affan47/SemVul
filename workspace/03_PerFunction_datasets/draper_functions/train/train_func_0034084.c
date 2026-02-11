gconf_locale_cache_free (GConfLocaleCache* cache)
{
  gconf_locale_cache_expire (cache, 0);

  g_assert(g_hash_table_size(cache->hash) == 0);

  g_hash_table_destroy(cache->hash);

  g_free(cache);
}
