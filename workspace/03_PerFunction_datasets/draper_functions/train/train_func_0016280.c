getttyname (const char *dev, dev_t mydev, ino64_t myino, int save, int *dostat)
{
  static size_t namelen;
  struct stat64 st;
  DIR *dirstream;
  struct dirent64 *d;
  size_t devlen = strlen (dev) + 1;

  dirstream = __opendir (dev);
  if (dirstream == NULL)
    {
      *dostat = -1;
      return NULL;
    }


  if (devlen < namelen)
    *((char *) __mempcpy (getttyname_name, dev, devlen - 1)) = '/';

  while ((d = __readdir64 (dirstream)) != NULL)
    if ((d->d_fileno == myino || *dostat)
	&& strcmp (d->d_name, "stdin")
	&& strcmp (d->d_name, "stdout")
	&& strcmp (d->d_name, "stderr"))
      {
	size_t dlen = _D_ALLOC_NAMLEN (d);
	if (devlen + dlen > namelen)
	  {
	    free (getttyname_name);
	    namelen = 2 * (devlen + dlen);
	    getttyname_name = malloc (namelen);
	    if (! getttyname_name)
	      {
		*dostat = -1;

		(void) __closedir (dirstream);
		return NULL;
	      }
	    *((char *) __mempcpy (getttyname_name, dev, devlen - 1)) = '/';
	  }
	memcpy (&getttyname_name[devlen], d->d_name, dlen);
	if (__xstat64 (_STAT_VER, getttyname_name, &st) == 0
#ifdef _STATBUF_ST_RDEV
	    && S_ISCHR (st.st_mode) && st.st_rdev == mydev
#else
	    && d->d_fileno == myino && st.st_dev == mydev
#endif
	   )
	  {
	    (void) __closedir (dirstream);
#if 0
	    __ttyname = getttyname_name;
#endif
	    __set_errno (save);
	    return getttyname_name;
	  }
      }

  (void) __closedir (dirstream);
  __set_errno (save);
  return NULL;
}
