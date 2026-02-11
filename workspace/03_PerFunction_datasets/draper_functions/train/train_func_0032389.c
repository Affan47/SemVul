qc_unlock (QC_Device * q)
{
  SANE_Status status;
  char lockfile[128];
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

  DBG (3, "qc_unlock: releasing lock for 0x%x\n", q->port);

#ifdef F_SETLK
  memset (&sfl, 0, sizeof (sfl));
#endif
  if (q->lock_fd < 0)
    {
      DBG (3, "qc_unlock; port was not locked\n");
      return SANE_STATUS_INVAL;
    }


#ifdef F_SETLK
  sfl.l_type = F_UNLCK;

  if (fcntl (q->lock_fd, F_SETLK, &sfl) != 0)
    {
      DBG (3, "qc_unlock: failed to release lock (%s)\n", strerror (errno));
      return SANE_STATUS_INVAL;
    }
#endif
  sprintf (lockfile, "/tmp/LOCK.qcam.0x%x", q->port);
  DBG (1, "qc_unlock: /tmp/LOCK.qcam.0x%x\n", q->port);
  unlink (lockfile);
  close (q->lock_fd);
  q->lock_fd = -1;
  DBG (1, "qc_unlock: exit\n");
  status = SANE_STATUS_GOOD;
  return status;
}
