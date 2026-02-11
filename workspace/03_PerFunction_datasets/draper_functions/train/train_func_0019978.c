dapselect(void)
{
  static char fnc[] = "dapselect";
  struct timeval timeout;
  struct timeval *tvpnext;
  struct timeval *tvp;
  int rc;


  fdscopy(fds_r, fds_ra);
  fdscopy(fds_w, fds_wa);
  fdscopy(fds_x, fds_xa);


  if (dapZeroTimeout) {
    tvp = &timeout;
    tvp->tv_sec = tvp->tv_usec = (long) (0);
  } else if ((tvpnext = timernext()) == (struct timeval *) (0)) {
#ifdef _AIX

    tvp = &timeout;
    tvp->tv_sec = (366 * 24 * 60 * 60) + 2;
    tvp->tv_usec = (long) (0);
#else
    tvp = (struct timeval *) (0);
#endif
  } else {
    tvp = &timeout;
    (void) tvdiff(tvpnext, tod(), tvp);
    if (tvp->tv_sec < 0) {
      tvp->tv_sec = tvp->tv_usec = (long) (0);
    }
    if (tvp->tv_sec > tv_select_max.tv_sec) {
      tvp = &tv_select_max;
    }
  }

  if (((rc = select(fds_size, fds_ra, fds_wa, fds_xa, tvp)) < 0)
      && (errno != EINTR)) {
    Warn("%t %s(): error: select(): %m\n", fnc);
  }
  if (rc <= 0) {
    fdszero(fds_ra);
    fdszero(fds_wa);
    fdszero(fds_xa);
  }
  return;
}
