hwloc_alloc_heap(hwloc_topology_t topology __hwloc_attribute_unused, size_t len)
{
  void *p;
#if defined(hwloc_getpagesize) && defined(HAVE_POSIX_MEMALIGN)
  errno = posix_memalign(&p, hwloc_getpagesize(), len);
  if (errno)
    p = NULL;
#elif defined(hwloc_getpagesize) && defined(HAVE_MEMALIGN)
  p = memalign(hwloc_getpagesize(), len);
#else
  p = malloc(len);
#endif
  return p;
}
