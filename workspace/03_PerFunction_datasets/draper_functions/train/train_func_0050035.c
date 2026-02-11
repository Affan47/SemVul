tar_extract_fifo(TAR *t, char *realname)
{
  mode_t mode;
  char *filename;
  char buf[T_BLOCKSIZE];
  char *pathname = 0;

  if (!TH_ISFIFO(t))
  {
    errno = EINVAL;
    return -1;
  }

  if (realname)
    {
    filename = realname;
    }
  else
    {
    pathname = th_get_pathname(t);
    filename = pathname;
    }
  mode = th_get_mode(t);


  strncpy(buf, filename, sizeof(buf)-1);
  buf[sizeof(buf)-1] = 0;

  if (mkdirhier(dirname(buf)) == -1)
    {
    if (pathname)
      {
      free(pathname);
      }
    return -1;
    }

#ifdef DEBUG
  printf("  ==> extracting: %s (fifo)\n", filename);
#endif
#ifndef WIN32
  if (mkfifo(filename, mode & 07777) == -1)
#else
    (void)mode;
#endif
  {
#ifdef DEBUG
    perror("mkfifo()");
#endif
    if (pathname)
      {
      free(pathname);
      }
    return -1;
  }

#ifndef WIN32
  if (pathname)
    {
    free(pathname);
    }
  return 0;
#endif
}
