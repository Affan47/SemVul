internal_memalign (alignment, size, file, line, flags)
     size_t alignment;
     size_t size;
     const char *file;
     int line, flags;
{
  register char *ptr;
  register char *aligned;
  register union mhead *p;

  ptr = internal_malloc (size + alignment, file, line, MALLOC_INTERNAL);

  if (ptr == 0)
    return 0;

  if (((long) ptr & (alignment - 1)) == 0)
    return ptr;

#if 0
  aligned = (char *) (((long) ptr + alignment - 1) & -alignment);
#else
  aligned = (char *) (((long) ptr + alignment - 1) & (~alignment + 1));
#endif


  p = (union mhead *) aligned - 1;
  p->mh_nbytes = aligned - ptr;
  p->mh_alloc = ISMEMALIGN;

  return aligned;
}
