do_pread (const char *path, int count, int64_t offset, size_t *size_r)
{
  int fd;

  CHROOT_IN;
  fd = open (path, O_RDONLY|O_CLOEXEC);
  CHROOT_OUT;

  if (fd == -1) {
    reply_with_perror ("open: %s", path);
    return NULL;
  }

  return pread_fd (fd, count, offset, size_r, path);
}
