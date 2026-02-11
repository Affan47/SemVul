readAll(int fd, void *buf, size_t count)
{
  ssize_t rc;
  char *ptr = (char *) buf;
  size_t num_read = 0;
  for (num_read = 0; num_read < count;) {
    rc = _real_read (fd, ptr + num_read, count - num_read);
    if (rc == -1) {
      if (errno == EINTR || errno == EAGAIN)
	continue;
      else
        return -1;
    }
    else if (rc == 0)
      break;
    else
      num_read += rc;
  }
  return num_read;
}
