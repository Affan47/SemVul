__local_memcache_get(local_memcache_t *lmc,
    const char *key, size_t n_key, size_t *n_value) {
  if (!lmc_lock_shm_region("local_memcache_get", lmc)) return 0;
  const char *r = ht_get(lmc->base, lmc->va_hash, key, n_key, n_value);
  return r;
}
