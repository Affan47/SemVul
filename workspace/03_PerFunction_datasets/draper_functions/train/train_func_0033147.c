atotv(A aobj, struct timeval *tvp)
{
  struct timeval timeleft, now;
  F fseconds;

  ipcWarn(0,"%t atotv\n");
  if (Ft==aobj->t && 1==aobj->n) {
    fseconds = *(F *)(aobj->p);
    gettimeofday(&now,NULL);
    timeleft.tv_sec = (int)(floor(fseconds));
    timeleft.tv_usec = (int)(1000000.0*(fseconds-floor(fseconds)));
    tvsum(&now,&timeleft,tvp);
    return tvp;
  }
  else if (It==aobj->t && 1<=aobj->n && 3>=aobj->n) {
    if (3==aobj->n && 1==aobj->p[2]) {
      if (0>aobj->p[1]) return 0;
      tvp->tv_sec=aobj->p[0];
      tvp->tv_usec=aobj->p[1];
    } else {
      gettimeofday(&now,NULL);
      timeleft.tv_sec=aobj->p[0];
      timeleft.tv_usec=(2<=aobj->n)?aobj->p[1]:0;
      tvsum(&now,&timeleft,tvp);
    }
    return tvp;
  } else return 0;
}
