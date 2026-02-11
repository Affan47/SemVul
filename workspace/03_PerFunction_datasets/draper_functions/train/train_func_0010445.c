AllocInternal(size_t size, size_t* actual_size,
                                         size_t alignment) {

  size_t extra = 0;
  if (alignment > big_page_size_) {
    extra = alignment - big_page_size_;
  }


  off_t limit = FLAGS_memfs_malloc_limit_mb*1024*1024;
  if (limit > 0 && hugetlb_base_ + size + extra > limit) {

    if (limit - hugetlb_base_ < big_page_size_) {
      Log(kLog, __FILE__, __LINE__, "reached memfs_malloc_limit_mb");
      failed_ = true;
    }
    else {
      Log(kLog, __FILE__, __LINE__,
          "alloc too large (size, bytes left)", size, limit-hugetlb_base_);
    }
    return NULL;
  }


  int ret = ftruncate(hugetlb_fd_, hugetlb_base_ + size + extra);
  if (ret != 0 && errno != EINVAL) {
    Log(kLog, __FILE__, __LINE__,
        "ftruncate failed", strerror(errno));
    failed_ = true;
    return NULL;
  }


  void *result;
  result = mmap(0, size + extra, PROT_WRITE|PROT_READ,
                FLAGS_memfs_malloc_map_private ? MAP_PRIVATE : MAP_SHARED,
                hugetlb_fd_, hugetlb_base_);
  if (result == reinterpret_cast<void*>(MAP_FAILED)) {
    if (!FLAGS_memfs_malloc_ignore_mmap_fail) {
      Log(kLog, __FILE__, __LINE__,
          "mmap failed (size, error)", size + extra, strerror(errno));
      failed_ = true;
    }
    return NULL;
  }
  uintptr_t ptr = reinterpret_cast<uintptr_t>(result);


  size_t adjust = 0;
  if ((ptr & (alignment - 1)) != 0) {
    adjust = alignment - (ptr & (alignment - 1));
  }
  ptr += adjust;
  hugetlb_base_ += (size + extra);

  if (actual_size) {
    *actual_size = size + extra - adjust;
  }

  return reinterpret_cast<void*>(ptr);
}
