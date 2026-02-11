mpool_calloc(struct MP *mp, size_t nmemb, size_t size) {
  size_t needed = nmemb*size;
  void *ptr;

  if(!needed) return NULL;
  if((ptr = mpool_malloc(mp, needed)))
    memset(ptr, 0, needed);
  return ptr;
}
