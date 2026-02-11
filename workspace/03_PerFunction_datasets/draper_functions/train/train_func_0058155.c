local_memcache_get_new(local_memcache_t *lmc,
    const char *key, size_t n_key, size_t *n_value) {
  const char *r = __local_memcache_get(lmc, key, n_key, n_value);
  char *new_s = 0;
  if (r) {
    new_s = malloc(*n_value);
    memcpy(new_s, r, *n_value);
  }
  if (!lmc_unlock_shm_region("local_memcache_get_new", lmc)) return 0;
  return new_s;
}
