xwrite(int fd, const void *buf, size_t count)
{
  ssize_t nwritten = 0;
  ssize_t ret;

  while (nwritten < count) {
    ret = write(fd, buf, count);

    if (ret >= 0) {
      nwritten += ret;
    } else {
      if (errno == EINTR) {
        continue;
      } else {
        return ret;
      }
    }
  }

  return nwritten;
}
