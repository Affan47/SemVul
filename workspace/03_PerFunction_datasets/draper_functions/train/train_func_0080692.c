os_accept(int fd, struct irc_sockaddr* peer)
{
  struct sockaddr_native addr;
  socklen_t addrlen;
  int new_fd;

  addrlen = sizeof(addr);
  new_fd = accept(fd, (struct sockaddr*)&addr, &addrlen);
  if (new_fd < 0)
    memset(peer, 0, sizeof(*peer));
  else
    sockaddr_to_irc(&addr, peer);
  return new_fd;
}
