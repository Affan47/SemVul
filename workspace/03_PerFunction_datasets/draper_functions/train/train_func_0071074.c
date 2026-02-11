bfd_realloc_or_free (void *ptr, bfd_size_type size)
{
  size_t amount = (size_t) size;
  void *ret;

  if (size != amount)
    ret = NULL;
  else if (ptr == NULL)
    ret = malloc (amount);
  else
    ret = realloc (ptr, amount);

  if (ret == NULL)
    {
      if (amount > 0)
	bfd_set_error (bfd_error_no_memory);

      if (ptr != NULL)
	free (ptr);
    }

  return ret;
}
