Access_mmap_offset_rw (int *remainder, int fd, off_t offset, size_t length, size_t eltsize, bool randomp) {
#ifdef HAVE_CADDR_T
  caddr_t memory;
#else
  void *memory;
#endif

  if (length == 0) {
    abort();
  }

  *remainder = offset % get_pagesize();
  offset -= (off_t) *remainder;
  length += (size_t) *remainder;

  if (sizeof(size_t) <= 4 && length > MAX32BIT) {
    debug(printf("Too big to mmap\n"));
    memory = NULL;
  } else {
    memory = mmap(NULL,length,PROT_READ|PROT_WRITE,0
#ifdef HAVE_MMAP_MAP_SHARED
		  |MAP_SHARED
#endif
#ifdef HAVE_MMAP_MAP_FILE
		  |MAP_FILE
#endif
#ifdef HAVE_MMAP_MAP_VARIABLE
		  |MAP_VARIABLE
#endif
		  ,fd,offset);
    if (memory == MAP_FAILED) {
      fprintf(stderr,"Got mmap failure on offset %lu, length %lu.  Error %d: %s\n",
	      offset,length,errno,strerror(errno));
      debug(printf("Got MAP_FAILED on offset %lu, length %lu\n",offset,length));
      memory = NULL;
    } else if (randomp == true) {
      debug(printf("Got mmap of %lu bytes at %p to %p\n",length,memory,memory+length-1));
#ifdef HAVE_MADVISE
#ifdef HAVE_MADVISE_MADV_RANDOM
      madvise(memory,length,MADV_RANDOM);
#endif
#endif
    } else {
      debug(printf("Got mmap of %lu bytes at %p to %p\n",length,memory,memory+length-1));
#ifdef HAVE_MADVISE
#ifdef HAVE_MADVISE_MADV_DONTNEED
      madvise(memory,length,MADV_DONTNEED);
#endif
#endif
    }
  }

  return memory;
}
