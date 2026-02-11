move_to_high_fd (fd, check_new, maxfd)
     int fd, check_new, maxfd;
{
  int script_fd, nfds, ignore;

  if (maxfd < 20)
    {
      nfds = getdtablesize ();
      if (nfds <= 0)
	nfds = 20;
      if (nfds > HIGH_FD_MAX)
	nfds = HIGH_FD_MAX;
    }
  else
    nfds = maxfd;

  for (nfds--; check_new && nfds > 3; nfds--)
    if (fcntl (nfds, F_GETFD, &ignore) == -1)
      break;

  if (nfds > 3 && fd != nfds && (script_fd = dup2 (fd, nfds)) != -1)
    {
      if (check_new == 0 || fd != fileno (stderr))
	close (fd);
      return (script_fd);
    }


  return (fd);
}
