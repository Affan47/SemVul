rtime (struct sockaddr_in *addrp, struct rpc_timeval *timep,
       struct rpc_timeval *timeout)
{
  int s;
  struct pollfd fd;
  int milliseconds;
  int res;

  uint32_t thetime;
  struct sockaddr_in from;
  socklen_t fromlen;
  int type;

  if (timeout == NULL)
    type = SOCK_STREAM;
  else
    type = SOCK_DGRAM;

  s = __socket (AF_INET, type, 0);
  if (s < 0)
    return (-1);

  addrp->sin_family = AF_INET;
  addrp->sin_port = htons (IPPORT_TIMESERVER);
  if (type == SOCK_DGRAM)
    {
      res = __sendto (s, (char *) &thetime, sizeof (thetime), 0,
		      (struct sockaddr *) addrp, sizeof (*addrp));
      if (res < 0)
	{
	  do_close (s);
	  return -1;
	}
      milliseconds = (timeout->tv_sec * 1000) + (timeout->tv_usec / 1000);
      fd.fd = s;
      fd.events = POLLIN;
      do
	res = __poll (&fd, 1, milliseconds);
      while (res < 0 && errno == EINTR);
      if (res <= 0)
	{
	  if (res == 0)
	    __set_errno (ETIMEDOUT);
	  do_close (s);
	  return (-1);
	}
      fromlen = sizeof (from);
      res = __recvfrom (s, (char *) &thetime, sizeof (thetime), 0,
			(struct sockaddr *) &from, &fromlen);
      do_close (s);
      if (res < 0)
	return -1;
    }
  else
    {
      if (__connect (s, (struct sockaddr *) addrp, sizeof (*addrp)) < 0)
	{
	  do_close (s);
	  return -1;
	}
      res = __read (s, (char *) &thetime, sizeof (thetime));
      do_close (s);
      if (res < 0)
	return (-1);
    }
  if (res != sizeof (thetime))
    {
      __set_errno (EIO);
      return -1;
    }
  thetime = ntohl (thetime);
  timep->tv_sec = thetime - TOFFSET;
  timep->tv_usec = 0;
  return 0;
}
