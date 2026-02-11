rfio_mstat_reset()
{
  int i,Tid;
  int rc = 0;

  INIT_TRACE("RFIO_TRACE");

  Cglobals_getTid(&Tid);

  TRACE(3,"rfio","rfio_mstat_reset entered, Tid=%d", Tid);

  TRACE(3,"rfio","rfio_mstat_reset: Lock mstat_tab");
  if (Cmutex_lock((void *) mstat_tab,-1) != 0) {
    TRACE(3,"rfio","rfio_mstat_reset: Cmutex_lock(mstat_tab,-1) error No %d (%s)", errno, strerror(errno));
    END_TRACE();
    return(-1);
  }
  for (i = 0; i < MAXMCON; i++) {
    if ((mstat_tab[i].s >= 0) && (mstat_tab[i].host[0] != '\0')) {
        TRACE(3,"rfio","rfio_mstat_reset: Resetting socket fd=%d, host=%s\n", mstat_tab[i].s, mstat_tab[i].host);
        netclose(mstat_tab[i].s);
    }
    mstat_tab[i].s = -1;
    mstat_tab[i].host[0] = '\0';
    mstat_tab[i].Tid = -1;
  }

  TRACE(3,"rfio","rfio_mstat_reset: Unlock mstat_tab");
  if (Cmutex_unlock((void *) mstat_tab) != 0) {
    TRACE(3,"rfio","rfio_mstat_reset: Cmutex_unlock(mstat_tab) error No %d (%s)", errno, strerror(errno));
    rc = -1;
  }

  END_TRACE();
  return(rc);
}
