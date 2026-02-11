raw_write (struct siobuf *sio, const char *buf, int len)
{
  int n, total, status;
  struct pollfd pollfd;

  assert (sio != NULL && buf != NULL);

  for (total = 0; total < len; total += n)
#ifdef USE_TLS
    if (sio->ssl != NULL)
      {


	while ((n = SSL_write (sio->ssl, buf, len)) <= 0)
	  if (sio_sslpoll (sio, n) <= 0)
	    return;
      }
    else
#endif
      {


	pollfd.fd = sio->sdw;
	pollfd.events = POLLOUT;
	errno = 0;
	while ((n = write (sio->sdw, buf + total, len - total)) < 0)
	  {
	    if (errno == EINTR)
	      continue;
	    if (errno != EAGAIN)
	      return;

	    pollfd.revents = 0;
	    while ((status = poll (&pollfd, 1, sio->milliseconds)) < 0)
	      if (errno != EINTR)
		return;
	    if (status == 0)
	      {
	        errno = ETIMEDOUT;
		return;
	      }
	    if (!(pollfd.revents & POLLOUT))
	      return;
	    errno = 0;
	  }
      }
}
