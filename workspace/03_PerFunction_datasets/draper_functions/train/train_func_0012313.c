bfd_zmalloc2 (bfd_size_type nmemb, bfd_size_type size)
{
  void *ptr;

  if ((nmemb | size) >= HALF_BFD_SIZE_TYPE
      && size != 0
      && nmemb > ~(bfd_size_type) 0 / size)
    {
      bfd_set_error (bfd_error_no_memory);
      return NULL;
    }

  size *= nmemb;

  if (size != (size_t) size)
    {
      bfd_set_error (bfd_error_no_memory);
      return NULL;
    }

  ptr = malloc ((size_t) size);

  if ((size_t) size != 0)
    {
      if (ptr == NULL)
	bfd_set_error (bfd_error_no_memory);
      else
	memset (ptr, 0, (size_t) size);
    }

  return ptr;
}
