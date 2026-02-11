_real_mremap(void *old_address, size_t old_size, size_t new_size,
    int flags, ...  ) {
  if (flags == MREMAP_FIXED) {
    va_list ap;
    va_start( ap, flags );
    void *new_address = va_arg ( ap, void * );
    va_end ( ap );
    REAL_FUNC_PASSTHROUGH_TYPED (void*, mremap)
      (old_address, old_size, new_size, flags, new_address);
  } else {
    REAL_FUNC_PASSTHROUGH_TYPED (void*, mremap)
      (old_address, old_size, new_size, flags);
  }
}
