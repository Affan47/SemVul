qc_lock_wait (QC_Device * q, int wait)
{
#ifdef F_SETLK

#ifndef HAVE_STRUCT_FLOCK
  struct flock
  {
    off_t l_start;
    off_t l_len;
    pid_t l_pid;
    short l_type;
    short l_whence;
  };
#endif
  struct flock sfl;
#endif

  DBG (3, "qc_lock_wait: acquiring lock for 0x%x\n", q->port);

#ifdef F_SETLK
  memset (&sfl, 0, sizeof (sfl));
#endif

  if (q->lock_fd < 0)
    {
      char lockfile[128];

      sprintf (lockfile, "/tmp/LOCK.qcam.0x%x", q->port);
      q->lock_fd = open (lockfile, O_WRONLY | O_CREAT | O_EXCL, 0666);
      if (q->lock_fd < 0)
	{
	  DBG (1, "qc_lock_wait: failed to open %s (%s)\n",
	       lockfile, strerror (errno));
	  return SANE_STATUS_INVAL;
	}

    }

#ifdef F_SETLK
  sfl.l_type = F_WRLCK;
  if (fcntl (q->lock_fd, wait ? F_SETLKW : F_SETLK, &sfl) != 0)
    {
      DBG (1, "qc_lock_wait: failed to acquire lock (%s)\n",
	   strerror (errno));
      return SANE_STATUS_INVAL;
    }
#endif

  DBG (3, "qc_lock_wait: got lock for 0x%x\n", q->port);
  return SANE_STATUS_GOOD;
}
