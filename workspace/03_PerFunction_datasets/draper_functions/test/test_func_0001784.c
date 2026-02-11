xcalloc (size_t nmemb, size_t size) {
  void *ptr = calloc (nmemb, size);
  if (ptr == NULL) return xmalloc_fatal(nmemb*size);
  return ptr;
}
