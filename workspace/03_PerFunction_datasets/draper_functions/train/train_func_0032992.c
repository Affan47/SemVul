set_limit (ind, newlim, mode)
     int ind;
     RLIMTYPE newlim;
     int mode;
{
#if defined (HAVE_RESOURCE)
   struct rlimit limit;
   RLIMTYPE val;
#endif

  if (limits[ind].parameter >= 256)
    switch (limits[ind].parameter)
      {
      case RLIMIT_FILESIZE:
#if !defined (HAVE_RESOURCE)
	return (ulimit (2, newlim / 512L));
#else
	errno = EINVAL;
	return -1;
#endif

      case RLIMIT_OPENFILES:
#if defined (HAVE_SETDTABLESIZE)
#  if defined (__CYGWIN__)

	setdtablesize (newlim);
	return 0;
#  else
	return (setdtablesize (newlim));
#  endif
#endif
      case RLIMIT_PIPESIZE:
      case RLIMIT_VIRTMEM:
      case RLIMIT_MAXUPROC:
      default:
	errno = EINVAL;
	return -1;
      }
  else
    {
#if defined (HAVE_RESOURCE)
      if (getrlimit (limits[ind].parameter, &limit) < 0)
	return -1;
#  if defined (HPUX9)
      if (limits[ind].parameter == RLIMIT_FILESIZE)
	newlim /= 512;
#  endif
      val = (current_user.euid != 0 && newlim == RLIM_INFINITY &&
	       (mode & LIMIT_HARD) == 0 &&
	       (limit.rlim_cur <= limit.rlim_max))
		 ? limit.rlim_max : newlim;
      if (mode & LIMIT_SOFT)
	limit.rlim_cur = val;
      if (mode & LIMIT_HARD)
	limit.rlim_max = val;

      return (setrlimit (limits[ind].parameter, &limit));
#else
      errno = EINVAL;
      return -1;
#endif
    }
}
