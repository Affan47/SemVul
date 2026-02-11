Alloc(size_t size, size_t *actual_size,
                                size_t alignment) {
#ifndef HAVE_MMAP
  return NULL;
#else
  static bool initialized = false;
  static off_t physmem_base;
  static off_t physmem_limit;
  static int physmem_fd;


  if (FLAGS_malloc_devmem_start == 0) {


    return NULL;
  }

  if (!initialized) {
    physmem_fd = open("/dev/mem", O_RDWR);
    if (physmem_fd < 0) {
      return NULL;
    }
    physmem_base = FLAGS_malloc_devmem_start*1024LL*1024LL;
    physmem_limit = FLAGS_malloc_devmem_limit*1024LL*1024LL;
    initialized = true;
  }


  if (pagesize == 0) pagesize = getpagesize();
  if (alignment < pagesize) alignment = pagesize;
  size_t aligned_size = ((size + alignment - 1) / alignment) * alignment;
  if (aligned_size < size) {
    return NULL;
  }
  size = aligned_size;


  if (actual_size) {
    *actual_size = size;
  }


  size_t extra = 0;
  if (alignment > pagesize) {
    extra = alignment - pagesize;
  }


  if (physmem_limit != 0 &&
      ((size + extra) > (physmem_limit - physmem_base))) {
    return NULL;
  }


  void *result = mmap(0, size + extra, PROT_WRITE|PROT_READ,
                      MAP_SHARED, physmem_fd, physmem_base);
  if (result == reinterpret_cast<void*>(MAP_FAILED)) {
    return NULL;
  }
  uintptr_t ptr = reinterpret_cast<uintptr_t>(result);


  size_t adjust = 0;
  if ((ptr & (alignment - 1)) != 0) {
    adjust = alignment - (ptr & (alignment - 1));
  }


  if (adjust > 0) {
    munmap(reinterpret_cast<void*>(ptr), adjust);
  }
  if (adjust < extra) {
    munmap(reinterpret_cast<void*>(ptr + adjust + size), extra - adjust);
  }

  ptr += adjust;
  physmem_base += adjust + size;

  return reinterpret_cast<void*>(ptr);
#endif
}
