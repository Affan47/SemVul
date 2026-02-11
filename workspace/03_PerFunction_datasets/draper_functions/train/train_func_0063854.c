do_truncate_size (const char *path, int64_t size)
{
  int fd;
  int r;

  CHROOT_IN;
  fd = open (path, O_WRONLY|O_NOCTTY|O_CLOEXEC);
  CHROOT_OUT;

  if (fd == -1) {
    reply_with_perror ("open: %s", path);
    return -1;
  }

  r = ftruncate (fd, (off_t) size);
  if (r == -1) {
    reply_with_perror ("ftruncate: %s", path);
    close (fd);
    return -1;
  }

  if (close (fd) == -1) {
    reply_with_perror ("close: %s", path);
    return -1;
  }

  return 0;
}
