stilloob (int s)
{
  static struct timeval timeout = { 0, 0 };
  fd_set excepts;
  int value;

  do
    {
      FD_ZERO (&excepts);
      FD_SET (s, &excepts);
      value = select (s + 1, (fd_set *) 0, (fd_set *) 0, &excepts, &timeout);
    }
  while (value == -1 && errno == EINTR);

  if (value < 0)
    fatalperror (pty, "select");

  return FD_ISSET (s, &excepts);
}
