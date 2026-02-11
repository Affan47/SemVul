_rl_input_available ()
{
#if defined(HAVE_SELECT)
  fd_set readfds, exceptfds;
  struct timeval timeout;
#endif
#if !defined (HAVE_SELECT) && defined(FIONREAD)
  int chars_avail;
#endif
  int tty;

  tty = fileno (rl_instream);

#if defined (HAVE_SELECT)
  FD_ZERO (&readfds);
  FD_ZERO (&exceptfds);
  FD_SET (tty, &readfds);
  FD_SET (tty, &exceptfds);
  timeout.tv_sec = 0;
  timeout.tv_usec = _keyboard_input_timeout;
  return (select (tty + 1, &readfds, (fd_set *)NULL, &exceptfds, &timeout) > 0);
#else

#if defined (FIONREAD)
  if (ioctl (tty, FIONREAD, &chars_avail) == 0)
    return (chars_avail);
#endif

#endif

#if defined (__MINGW32__)
  if (isatty (tty))
    return (_kbhit ());
#endif

  return 0;
}
