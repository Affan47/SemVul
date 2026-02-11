gst_poll_fd_has_error (const GstPoll * set, GstPollFD * fd)
{
  gboolean res = FALSE;
  gint idx;

  g_return_val_if_fail (set != NULL, FALSE);
  g_return_val_if_fail (fd != NULL, FALSE);
  g_return_val_if_fail (fd->fd >= 0, FALSE);

  GST_DEBUG ("%p: fd (fd:%d, idx:%d)", set, fd->fd, fd->idx);

  g_mutex_lock (set->lock);

  idx = find_index (set->active_fds, fd);
  if (idx >= 0) {
#ifndef G_OS_WIN32
    struct pollfd *pfd = &g_array_index (set->active_fds, struct pollfd, idx);

    res = (pfd->revents & (POLLERR | POLLNVAL)) != 0;
#else
    WinsockFd *wfd = &g_array_index (set->active_fds, WinsockFd, idx);

    res = (wfd->events.iErrorCode[FD_CLOSE_BIT] != 0) ||
        (wfd->events.iErrorCode[FD_READ_BIT] != 0) ||
        (wfd->events.iErrorCode[FD_WRITE_BIT] != 0) ||
        (wfd->events.iErrorCode[FD_ACCEPT_BIT] != 0) ||
        (wfd->events.iErrorCode[FD_CONNECT_BIT] != 0);
#endif
  } else {
    GST_WARNING ("%p: couldn't find fd !", set);
  }

  g_mutex_unlock (set->lock);

  return res;
}
