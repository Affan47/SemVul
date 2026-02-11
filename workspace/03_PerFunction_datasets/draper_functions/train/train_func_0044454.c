signalfd_init(void)
{
  if (pipe(fds) == -1)
    return -1;
  if (!cloexec_on(fds[0])
      || !nonblock_on(fds[0])
      || !cloexec_on(fds[1])
      || !nonblock_on(fds[1]))
    signalfd_close();
  return fds[0];
}
