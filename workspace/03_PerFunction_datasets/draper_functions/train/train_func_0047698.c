rfio_end_this(s,flag)
     int s;
     int flag;
{
  int i,Tid, j=0 ;
  char buf[RQSTSIZE];
  int found = 0;
  char *p=buf ;
  int rc = 0;


  memset(buf, 0, RQSTSIZE);

  Cglobals_getTid(&Tid);

  TRACE(3,"rfio","rfio_end_this(s=%d,flag=%d) entered, Tid=%d", s, flag, Tid);

  TRACE(3,"rfio","rfio_end: Lock mstat_tab");
  if (Cmutex_lock((void *) mstat_tab,-1) != 0) {
    TRACE(3,"rfio","rfio_end_this: Cmutex_lock(mstat_tab,-1) error No %d (%s)", errno, strerror(errno));
    return(-1);
  }
  for (i = 0; i < MAXMCON; i++) {
    if (mstat_tab[i].Tid == Tid) {
      if ((mstat_tab[i].s == s) && (mstat_tab[i].host[0] != '\0')) {
        found++;
        if (flag) {
          marshall_WORD(p, RFIO_MAGIC);
          marshall_WORD(p, RQST_END);
          marshall_LONG(p, j);
          TRACE(3,"rfio","rfio_end_this: close(mstat_tab[%d].s=%d), host=%s, Tid=%d",i,mstat_tab[i].s, mstat_tab[i].host, Tid);
          if (netwrite_timeout(mstat_tab[i].s,buf,RQSTSIZE,RFIO_CTRL_TIMEOUT) != RQSTSIZE) {
            TRACE(3, "rfio", "rfio_end_this: netwrite_timeout(): ERROR occured (errno=%d), Tid=%d", errno, Tid);
          }
        }
        netclose(mstat_tab[i].s);
        mstat_tab[i].s = -1;
        mstat_tab[i].host[0] = '\0';
        mstat_tab[i].Tid = -1;
      }
    }
  }
  if (! found) netclose(s);

  TRACE(3,"rfio","rfio_end: Unlock mstat_tab");
  if (Cmutex_unlock((void *) mstat_tab) != 0) {
    TRACE(3,"rfio","rfio_end_this: Cmutex_unlock(mstat_tab) error No %d (%s)", errno, strerror(errno));
    rc = -1;
  }

  return(rc);
}
