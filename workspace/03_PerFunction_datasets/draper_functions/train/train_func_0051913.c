do_zero (const char *device)
{
  char buf[sizeof zero_buf];
  int fd;
  size_t i, offset;

  fd = open (device, O_RDWR|O_CLOEXEC);
  if (fd == -1) {
    reply_with_perror ("%s", device);
    return -1;
  }

  for (i = 0; i < 32; ++i) {
    offset = i * sizeof zero_buf;


    if (pread (fd, buf, sizeof buf, offset) != sizeof buf) {
      reply_with_perror ("pread: %s", device);
      close (fd);
      return -1;
    }

    if (!is_zero (buf, sizeof buf)) {
      if (pwrite (fd, zero_buf, sizeof zero_buf, offset) != sizeof zero_buf) {
        reply_with_perror ("pwrite: %s", device);
        close (fd);
        return -1;
      }
    }

    notify_progress ((uint64_t) i, 32);
  }

  if (close (fd) == -1) {
    reply_with_perror ("close: %s", device);
    return -1;
  }

  return 0;
}
