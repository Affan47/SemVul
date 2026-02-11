cache_bmmap (struct bfd *abfd ATTRIBUTE_UNUSED,
	     void *addr ATTRIBUTE_UNUSED,
	     bfd_size_type len ATTRIBUTE_UNUSED,
	     int prot ATTRIBUTE_UNUSED,
	     int flags ATTRIBUTE_UNUSED,
	     file_ptr offset ATTRIBUTE_UNUSED,
             void **map_addr ATTRIBUTE_UNUSED,
             bfd_size_type *map_len ATTRIBUTE_UNUSED)
{
  void *ret = (void *) -1;

  if ((abfd->flags & BFD_IN_MEMORY) != 0)
    abort ();
#ifdef HAVE_MMAP
  else
    {
      static uintptr_t pagesize_m1;
      FILE *f;
      file_ptr pg_offset;
      bfd_size_type pg_len;

      f = bfd_cache_lookup (abfd, CACHE_NO_SEEK_ERROR);
      if (f == NULL)
	return ret;

      if (pagesize_m1 == 0)
        pagesize_m1 = getpagesize () - 1;


      if (abfd->my_archive != NULL)
        offset += abfd->origin;


      pg_offset = offset & ~pagesize_m1;
      pg_len = (len + (offset - pg_offset) + pagesize_m1) & ~pagesize_m1;

      ret = mmap (addr, pg_len, prot, flags, fileno (f), pg_offset);
      if (ret == (void *) -1)
	bfd_set_error (bfd_error_system_call);
      else
        {
          *map_addr = ret;
          *map_len = pg_len;
          ret += offset & pagesize_m1;
        }
    }
#endif

  return ret;
}
