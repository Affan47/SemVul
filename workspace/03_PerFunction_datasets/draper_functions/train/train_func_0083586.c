eio__readahead (int fd, off_t offset, size_t count, etp_worker *self)
{
  size_t todo = count;
  dBUF;

  while (todo > 0)
    {
      size_t len = todo < EIO_BUFSIZE ? todo : EIO_BUFSIZE;

      pread (fd, eio_buf, len, offset);
      offset += len;
      todo   -= len;
    }

  errno = 0;
  return count;
}
