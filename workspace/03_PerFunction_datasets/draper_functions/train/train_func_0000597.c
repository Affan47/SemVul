readyToRead(int fd) {
  fd_set readfds;
  struct timeval zeroTimeout = {0, 0};
  FD_ZERO(&readfds);
  FD_SET(fd, &readfds);
  select(fd + 1, &readfds, NULL, NULL, &zeroTimeout);
  return FD_ISSET(fd, &readfds);
}
