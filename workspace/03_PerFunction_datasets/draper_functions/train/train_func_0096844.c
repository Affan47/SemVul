get_random_fd(void)
{
  struct timeval  tv;
  static int  fd = -2;
  int    i;

  if (fd == -2) {
    gettimeofday(&tv, 0);
    fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1)
      fd = open("/dev/random", O_RDONLY | O_NONBLOCK);
    srand((getpid() << 16) ^ getuid() ^ tv.tv_sec ^ tv.tv_usec);
  }

  gettimeofday(&tv, 0);
  for (i = (tv.tv_sec ^ tv.tv_usec) & 0x1F; i > 0; i--)
    rand();
  return fd;
}
