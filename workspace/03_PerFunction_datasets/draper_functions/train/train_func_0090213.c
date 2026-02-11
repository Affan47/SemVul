get_limit (ind, softlim, hardlim)
     int ind;
     RLIMTYPE *softlim, *hardlim;
{
  RLIMTYPE value;
#if defined (HAVE_RESOURCE)
  struct rlimit limit;
#endif

  if (limits[ind].parameter >= 256)
    {
      switch (limits[ind].parameter)
	{
	case RLIMIT_FILESIZE:
	  if (filesize (&value) < 0)
	    return -1;
	  break;
	case RLIMIT_PIPESIZE:
	  if (pipesize (&value) < 0)
	    return -1;
	  break;
	case RLIMIT_OPENFILES:
	  value = (RLIMTYPE)getdtablesize ();
	  break;
	case RLIMIT_VIRTMEM:
	  return (getmaxvm (softlim, hardlim));
	case RLIMIT_MAXUPROC:
	  if (getmaxuprc (&value) < 0)
	    return -1;
	  break;
	default:
	  errno = EINVAL;
	  return -1;
	}
      *softlim = *hardlim = value;
      return (0);
    }
  else
    {
#if defined (HAVE_RESOURCE)
      if (getrlimit (limits[ind].parameter, &limit) < 0)
	return -1;
      *softlim = limit.rlim_cur;
      *hardlim = limit.rlim_max;
#  if defined (HPUX9)
      if (limits[ind].parameter == RLIMIT_FILESIZE)
	{
	  *softlim *= 512;
	  *hardlim *= 512;
	}
      else
#  endif
      return 0;
#else
      errno = EINVAL;
      return -1;
#endif
    }
}
