tio_select(TFILE *fp, int readfd, const struct timeval *deadline)
{
  struct timeval tv;
  fd_set fdset;
  int rv;
  while (1)
  {

    FD_ZERO(&fdset);
    FD_SET(fp->fd,&fdset);

    if (tio_tv_remaining(&tv,deadline))
    {
      errno=ETIME;
      return -1;
    }

    if (readfd)
    {

      if (tv.tv_sec>fp->readtimeout.tv_sec)
        tv.tv_sec=fp->readtimeout.tv_sec;
      rv=select(FD_SETSIZE,&fdset,NULL,NULL,&tv);
    }
    else
    {

      if (tv.tv_sec>fp->writetimeout.tv_sec)
        tv.tv_sec=fp->writetimeout.tv_sec;
      rv=select(FD_SETSIZE,NULL,&fdset,NULL,&tv);
    }
    if (rv>0)
      return 0;
    else if (rv==0)
    {

      errno=ETIME;
      return -1;
    }
    else if (errno!=EINTR)

      return -1;

  }
}
