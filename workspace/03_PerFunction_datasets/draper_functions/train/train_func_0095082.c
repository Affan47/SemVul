log_EWouldBlock(I i,I rc,I nern,C *path,C *fcn)
{
  if(-1==rc){
    if(EWOULDBLOCK==nern){
      syslog(LOG_NOTICE,
	     "A+ %s failed for '%s' after %d EWOULDBLOCKs",fcn,path,i);
    H("\343 A+ %s failed for '%s' after %ld tries\n",fcn,path,i);
    } else {
#ifndef HAVE_STRERROR
      syslog(LOG_INFO,
	     "A+ %s failed for '%s' after %d EWOULDBLOCKs with: %m",fcn,path,i);
      H("\343 A+ %s failed for '%s' after %ld tries with: %s\n",
	fcn,path,i,(nern<sys_nerr)?sys_errlist[nern]:"unknown system error");
#else
      char *errstr=strerror(nern);
      syslog(LOG_INFO,
	     "A+ %s failed for '%s' after %d EWOULDBLOCKs with: %m",fcn,path,i);
      H("\343 A+ %s failed for '%s' after %ld tries with: %s\n",
	fcn,path,i,errstr?errstr:"unknown system error");
#endif
    }
  } else {
    syslog(LOG_INFO,
	   "A+ %s succeeded for '%s' after %d EWOULDBLOCKs",fcn,path,i);
    H("\343 A+ %s succeeded for '%s' after %ld tries\n",fcn,path,i);
  }
  R nern;
}
