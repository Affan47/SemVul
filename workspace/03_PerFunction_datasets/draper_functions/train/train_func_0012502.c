get_flags (void)
  {
    int flags;

    if (ioctl(ppp_fd, PPPIOCGFLAGS, (caddr_t) &flags) < 0)
      {
	if ( ok_error (errno) )
	  {
	    flags = 0;
	  }
	else
	  {
	    syslog(LOG_ERR, "ioctl(PPPIOCGFLAGS): %m");
	    quit();
	  }
      }

    SYSDEBUG ((LOG_DEBUG, "get flags = %x\n", flags));
    return flags;
  }
