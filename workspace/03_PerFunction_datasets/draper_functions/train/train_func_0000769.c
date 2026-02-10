ReadPersistent(const int fd, void *buf, const size_t count) {
  CHECK_GE(fd, 0);
  char *buf0 = reinterpret_cast<char *>(buf);
  ssize_t num_bytes = 0;
  while (num_bytes < count) {
    ssize_t len;
    NO_INTR(len = read(fd, buf0 + num_bytes, count - num_bytes));
    if (len < 0) {
      return -1;
    }
    if (len == 0) {
      break;
    }
    num_bytes += len;
  }
  CHECK(num_bytes <= count);
  return num_bytes;
}
