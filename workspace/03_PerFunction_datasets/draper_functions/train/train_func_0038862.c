check_net_or_keyboard_input(socket_st* hd)
{
  int maxfd;
  fd_set rset;
  int err;
  struct timeval tv;

  do
    {
      FD_ZERO (&rset);
      FD_SET (fileno (stdin), &rset);
      FD_SET (hd->fd, &rset);

      maxfd = MAX (fileno (stdin), hd->fd);
      tv.tv_sec = 0;
      tv.tv_usec = 500 * 1000;

      if (hd->secure == 1)
        if (gnutls_record_check_pending(hd->session))
          return IN_NET;

      err = select (maxfd + 1, &rset, NULL, NULL, &tv);
      if (err < 0)
        continue;

      if (FD_ISSET (hd->fd, &rset))
        return IN_NET;


      if (FD_ISSET (fileno (stdin), &rset))
        return IN_KEYBOARD;
    }
  while(err == 0);

  return IN_NONE;
}
