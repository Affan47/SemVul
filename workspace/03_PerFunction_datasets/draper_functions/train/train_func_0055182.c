setup_socket(va_list args)
{
  int fd = va_arg(args, int);
  int opt = 1;

  setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));

#ifdef IPTOS_LOWDELAY
  opt = IPTOS_LOWDELAY;
  setsockopt(fd, IPPROTO_IP, IP_TOS, &opt, sizeof(opt));
#endif

  fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);

  return NULL;
}
