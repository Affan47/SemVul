hts_cache_free(t_dnscache *const root) {
  if (root != NULL) {
    t_dnscache *cache;
    for(cache = root; cache != NULL; ) {
      t_dnscache *const next = cache->n;
      cache->n = NULL;
      freet(cache);
      cache = next;
    }
  }
}
