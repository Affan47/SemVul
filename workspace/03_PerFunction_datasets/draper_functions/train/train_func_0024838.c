lofstat(int fd,struct stat *buf)
{
  int i=0,st=1,rc=0;
  static C fcn[] = "fstat";
  while(i<10&&-1==(rc=fstat(fd,buf))&&EWOULDBLOCK==errno)
  {sleep(st);if(8>st)st*=2;++i;}
  if (i) errno=log_EWouldBlock(i,rc,errno,"...",fcn);
  R rc;
}
