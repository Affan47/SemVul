fcollfs_read (void *cookie, char *b, size_t s)
{
  int fd;
  fcollfs_cookie_t *c;

  c = (fcollfs_cookie_t *) cookie;
  fd = c->fd;

  return __collfs_libc_read(fd, b, s);
}
