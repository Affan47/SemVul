getttyname_r (char *buf, size_t buflen, dev_t mydev, ino64_t myino,
	      int save, int *dostat)
{
  struct stat64 st;
  DIR *dirstream;
  struct dirent64 *d;
  size_t devlen = strlen (buf);

  dirstream = __opendir (buf);
  if (dirstream == NULL)
    {
      *dostat = -1;
      return errno;
    }

  while ((d = __readdir64 (dirstream)) != NULL)
    if ((d->d_fileno == myino || *dostat)
	&& strcmp (d->d_name, "stdin")
	&& strcmp (d->d_name, "stdout")
	&& strcmp (d->d_name, "stderr"))
      {
	char *cp;
	size_t needed = _D_EXACT_NAMLEN (d) + 1;

	if (needed > buflen)
	  {
	    *dostat = -1;
	    (void) __closedir (dirstream);
	    __set_errno (ERANGE);
	    return ERANGE;
	  }

	cp = __stpncpy (buf + devlen, d->d_name, needed);
	cp[0] = '\0';

	if (__xstat64 (_STAT_VER, buf, &st) == 0
#ifdef _STATBUF_ST_RDEV
	    && S_ISCHR (st.st_mode) && st.st_rdev == mydev
#else
	    && d->d_fileno == myino && st.st_dev == mydev
#endif
	   )
	  {
	    (void) __closedir (dirstream);
	    __set_errno (save);
	    return 0;
	  }
      }

  (void) __closedir (dirstream);
  __set_errno (save);


  return ENOTTY;
}
