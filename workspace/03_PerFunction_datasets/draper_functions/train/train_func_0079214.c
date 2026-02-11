read() {
  if (read_fd == -1) return -2;
  unsigned char item;
  ssize_t result;
  do {
    result = ::read(read_fd, &item, 1);
  } while (result == -1  && errno == EINTR);
  if (result > 0) return (int)item;
  return result;
}
