do_malloc(size_t size) {
  void* ret = do_malloc_no_errno(size);
  if (UNLIKELY(ret == NULL)) errno = ENOMEM;
  return ret;
}
