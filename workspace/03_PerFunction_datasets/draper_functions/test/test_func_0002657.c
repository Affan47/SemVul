validate_access (char **filep, int mode)
{
  struct stat stbuf;
  int fd;
  struct dirlist *dirp;
  static char *pathname = 0;
  char *filename = *filep;


  if (strstr (filename, "/../"))
    return (EACCESS);

  if (*filename == '/')
    {


      for (dirp = dirs; dirp->name != NULL; dirp++)
	{
	  if (dirp->len == 1 ||
	      (!strncmp (filename, dirp->name, dirp->len) &&
	       filename[dirp->len] == '/'))
	    break;
	}

      if (dirp->name == NULL && dirp != dirs)
	return (EACCESS);
      if (stat (filename, &stbuf) < 0)
	return (errno == ENOENT ? ENOTFOUND : EACCESS);
      if ((stbuf.st_mode & S_IFMT) != S_IFREG)
	return (ENOTFOUND);
      if (mode == RRQ)
	{
	  if ((stbuf.st_mode & S_IROTH) == 0)
	    return (EACCESS);
	}
      else
	{
	  if ((stbuf.st_mode & S_IWOTH) == 0)
	    return (EACCESS);
	}
    }
  else
    {
      int err;


      if (mode != RRQ || !strncmp (filename, "../", 3))
	return (EACCESS);


      err = ENOTFOUND;
      for (dirp = dirs; dirp->name != NULL; dirp++)
	{
	  free (pathname);
	  pathname = malloc (strlen (dirp->name) + 1 + strlen (filename) + 1);
	  if (!pathname)
	    return ENOMEM;
	  sprintf (pathname, "%s/%s", dirp->name, filename);
	  if (stat (pathname, &stbuf) == 0 &&
	      (stbuf.st_mode & S_IFMT) == S_IFREG)
	    {
	      if ((stbuf.st_mode & S_IROTH) != 0)
		{
		  break;
		}
	      err = EACCESS;
	    }
	}
      if (dirp->name == NULL)
	return (err);
      *filep = filename = pathname;
    }
  fd = open (filename, mode == RRQ ? O_RDONLY : (O_WRONLY | O_TRUNC));
  if (fd < 0)
    return (errno + 100);
  file = fdopen (fd, (mode == RRQ) ? "r" : "w");
  if (file == NULL)
    {
      return errno + 100;
    }
  return (0);
}
