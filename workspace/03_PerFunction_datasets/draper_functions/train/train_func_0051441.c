MagickMallocAligned(const size_t alignment,const size_t size)
{
  size_t
    alligned_size;

  void
    *alligned_p = 0;

  alligned_size=RoundUpToAlignment(size,alignment);

  if ((size == 0) || (alignment < sizeof(void *)) || (alligned_size < size))
    return ((void *) NULL);

#if defined(HAVE_POSIX_MEMALIGN)
  if (posix_memalign(&alligned_p, alignment, alligned_size) != 0)
    alligned_p=0;
#elif defined(HAVE__ALIGNED_MALLOC)
  alligned_p=_aligned_malloc(alligned_size,alignment);
#else
  {
    void
      *alloc_p;

    size_t
      alloc_size;

    alloc_size=(size+alignment-1)+sizeof(void *);
    if (alloc_size > size)
      {
	if ((alloc_p = ((MallocFunc)(alloc_size))) != NULL)
	  {
	    alligned_p=(void*) RoundUpToAlignment((magick_uintptr_t)alloc_p+
						  sizeof(void *),alignment);
	    *((void **)alligned_p-1)=alloc_p;
	  }
      }
  }
#endif

  return alligned_p;
}
