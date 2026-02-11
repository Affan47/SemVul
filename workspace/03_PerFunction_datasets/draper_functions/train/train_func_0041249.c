scm_std_select (int nfds,
		SELECT_TYPE *readfds,
		SELECT_TYPE *writefds,
		SELECT_TYPE *exceptfds,
		struct timeval *timeout)
{
  fd_set my_readfds;
  int res, eno, wakeup_fd;
  scm_i_thread *t = SCM_I_CURRENT_THREAD;
  scm_t_guile_ticket ticket;

  if (readfds == NULL)
    {
      FD_ZERO (&my_readfds);
      readfds = &my_readfds;
    }

  while (scm_i_setup_sleep (t, SCM_BOOL_F, NULL, t->sleep_pipe[1]))
    SCM_TICK;

  wakeup_fd = t->sleep_pipe[0];
  ticket = scm_leave_guile ();
  FD_SET (wakeup_fd, readfds);
  if (wakeup_fd >= nfds)
    nfds = wakeup_fd+1;
  res = select (nfds, readfds, writefds, exceptfds, timeout);
  t->sleep_fd = -1;
  eno = errno;
  scm_enter_guile (ticket);

  scm_i_reset_sleep (t);

  if (res > 0 && FD_ISSET (wakeup_fd, readfds))
    {
      char dummy;
      size_t count;

      count = read (wakeup_fd, &dummy, 1);

      FD_CLR (wakeup_fd, readfds);
      res -= 1;
      if (res == 0)
	{
	  eno = EINTR;
	  res = -1;
	}
    }
  errno = eno;
  return res;
}
