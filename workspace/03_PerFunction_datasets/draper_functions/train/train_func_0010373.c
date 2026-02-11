lto_read_section_data (struct lto_file_decl_data *file_data,
		       intptr_t offset, size_t len)
{
  char *result;
  static int fd = -1;
  static char *fd_name;
#if LTO_MMAP_IO
  intptr_t computed_len;
  intptr_t computed_offset;
  intptr_t diff;
#endif


  if (fd != -1
      && strcmp (fd_name, file_data->file_name) != 0)
    {
      free (fd_name);
      close (fd);
      fd = -1;
    }
  if (fd == -1)
    {
      fd = open (file_data->file_name, O_RDONLY|O_BINARY);
      if (fd == -1)
	return NULL;
      fd_name = xstrdup (file_data->file_name);
    }

#if LTO_MMAP_IO
  if (!page_mask)
    {
      size_t page_size = sysconf (_SC_PAGE_SIZE);
      page_mask = ~(page_size - 1);
    }

  computed_offset = offset & page_mask;
  diff = offset - computed_offset;
  computed_len = len + diff;

  result = (char *) mmap (NULL, computed_len, PROT_READ, MAP_PRIVATE,
			  fd, computed_offset);
  if (result == MAP_FAILED)
    return NULL;

  return result + diff;
#else
  result = (char *) xmalloc (len);
  if (lseek (fd, offset, SEEK_SET) != offset
      || read (fd, result, len) != (ssize_t) len)
    {
      free (result);
      result = NULL;
    }
#ifdef __MINGW32__


  free (fd_name);
  fd_name = NULL;
  close (fd);
  fd = -1;
#endif
  return result;
#endif
}
