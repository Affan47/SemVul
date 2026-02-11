pch_open_file (cpp_reader *pfile, _cpp_file *file, bool *invalid_pch)
{
  static const char extension[] = ".gch";
  const char *path = file->path;
  size_t len, flen;
  char *pchname;
  struct stat st;
  bool valid = false;


  if (file->name[0] == '\0' || !pfile->cb.valid_pch)
    return false;

  flen = strlen (path);
  len = flen + sizeof (extension);
  pchname = xmalloc (len);
  memcpy (pchname, path, flen);
  memcpy (pchname + flen, extension, sizeof (extension));

  if (stat (pchname, &st) == 0)
    {
      DIR *pchdir;
      struct dirent *d;
      size_t dlen, plen = len;

      if (!S_ISDIR (st.st_mode))
	valid = validate_pch (pfile, file, pchname);
      else if ((pchdir = opendir (pchname)) != NULL)
	{
	  pchname[plen - 1] = '/';
	  while ((d = readdir (pchdir)) != NULL)
	    {
	      dlen = strlen (d->d_name) + 1;
	      if ((strcmp (d->d_name, ".") == 0)
		  || (strcmp (d->d_name, "..") == 0))
		continue;
	      if (dlen + plen > len)
		{
		  len += dlen + 64;
		  pchname = xrealloc (pchname, len);
		}
	      memcpy (pchname + plen, d->d_name, dlen);
	      valid = validate_pch (pfile, file, pchname);
	      if (valid)
		break;
	    }
	  closedir (pchdir);
	}
      if (valid)
	file->pch = true;
      else
	*invalid_pch = true;
    }

  if (valid)
    file->pchname = pchname;
  else
    free (pchname);

  return valid;
}
