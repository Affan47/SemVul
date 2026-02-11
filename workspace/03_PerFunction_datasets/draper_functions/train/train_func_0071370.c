find_index (GArray * array, GstPollFD * fd)
{
#ifndef G_OS_WIN32
  struct pollfd *ifd;
#else
  WinsockFd *ifd;
#endif
  guint i;


  if (fd->idx >= 0 && fd->idx < array->len) {
#ifndef G_OS_WIN32
    ifd = &g_array_index (array, struct pollfd, fd->idx);
#else
    ifd = &g_array_index (array, WinsockFd, fd->idx);
#endif

    if (ifd->fd == fd->fd) {
      return fd->idx;
    }
  }


  for (i = 0; i < array->len; i++) {
#ifndef G_OS_WIN32
    ifd = &g_array_index (array, struct pollfd, i);
#else
    ifd = &g_array_index (array, WinsockFd, i);
#endif

    if (ifd->fd == fd->fd) {
      fd->idx = (gint) i;
      return fd->idx;
    }
  }

  fd->idx = -1;
  return fd->idx;
}
