__posix_openpt (oflag)
     int oflag;
{
  static int have_no_dev_ptmx;
  int fd;

  if (!have_no_dev_ptmx)
    {
      fd = __open (_PATH_DEVPTMX, oflag);
      if (fd != -1)
	{
	  struct statfs fsbuf;
	  static int devpts_mounted;


	  if (devpts_mounted
	      || (__statfs (_PATH_DEVPTS, &fsbuf) == 0
		  && fsbuf.f_type == DEVPTS_SUPER_MAGIC)
	      || (__statfs (_PATH_DEV, &fsbuf) == 0
		  && fsbuf.f_type == DEVFS_SUPER_MAGIC))
	    {

	      devpts_mounted = 1;
	      return fd;
	    }


	  __close (fd);
	  have_no_dev_ptmx = 1;
	  __set_errno (ENOENT);
	}
      else
	{
	  if (errno == ENOENT || errno == ENODEV)
	    have_no_dev_ptmx = 1;
	  else
	    return -1;
	}
    }
  else
    __set_errno (ENOENT);

  return -1;
}
