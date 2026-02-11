xsavedir(const char *dir, int flags)
{
  DIR *dirp;
  struct dirent *dp;
  struct savedir_dirinfo *result = NULL;
  struct new_savedir_direntry_internal *internal;

  size_t namebuf_allocated = 0u, namebuf_used = 0u;
  size_t entrybuf_allocated = 0u;
  int save_errno;

  dirp = opendir (dir);
  if (dirp == NULL)
    return NULL;

  errno = 0;
  result = xmalloc(sizeof(*result));
  result->buffer = NULL;
  result->size = 0u;
  result->entries = NULL;
  internal = NULL;

  while ((dp = readdir (dirp)) != NULL)
    {


      char const *entry = dp->d_name;
      if (entry[entry[0] != '.' ? 0 : entry[1] != '.' ? 1 : 2] != '\0')
	{

	  size_t entry_size = strlen (entry) + 1;
	  result->buffer = extendbuf(result->buffer, namebuf_used+entry_size, &namebuf_allocated);
	  memcpy ((result->buffer) + namebuf_used, entry, entry_size);


	  internal = extendbuf(internal, (1+result->size)*sizeof(*internal), &entrybuf_allocated);
	  internal[result->size].flags = 0;

#if defined HAVE_STRUCT_DIRENT_D_TYPE && defined USE_STRUCT_DIRENT_D_TYPE
	  internal[result->size].type_info = type_to_mode(dp->d_type);
	  if (dp->d_type != DT_UNKNOWN)
	    internal[result->size].flags |= SavedirHaveFileType;
#else
	  internal[result->size].type_info = 0;
#endif
	  internal[result->size].buffer_offset = namebuf_used;


	  ++(result->size);
	  namebuf_used += entry_size;
	}
    }

  result->buffer = extendbuf(result->buffer, namebuf_used+1, &namebuf_allocated);
  result->buffer[namebuf_used] = '\0';


  result->entries = convertentries(result, internal);
  free(internal);
  internal = NULL;


  if (flags & SavedirSort)
    {
      qsort(result->entries,
	    result->size, sizeof(*result->entries),
	    savedir_cmp);
    }


  save_errno = errno;
  if (CLOSEDIR (dirp) != 0)
    save_errno = errno;
  if (save_errno != 0)
    {
      free (result->buffer);
      free (result);
      errno = save_errno;
      return NULL;
    }

  return result;
}
