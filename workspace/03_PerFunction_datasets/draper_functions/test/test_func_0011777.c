gst_poll_fd_ctl_read_unlocked (GstPoll * set, GstPollFD * fd, gboolean active)
{
  gint idx;

  GST_DEBUG ("%p: fd (fd:%d, idx:%d), active : %d", set,
      fd->fd, fd->idx, active);

  idx = find_index (set->fds, fd);

  if (idx >= 0) {
#ifndef G_OS_WIN32
    struct pollfd *pfd = &g_array_index (set->fds, struct pollfd, idx);

    if (active)
      pfd->events |= (POLLIN | POLLPRI);
    else
      pfd->events &= ~(POLLIN | POLLPRI);
#else
    gst_poll_update_winsock_event_mask (set, idx, FD_READ | FD_ACCEPT, active);
#endif
    MARK_REBUILD (set);
  } else {
    GST_WARNING ("%p: couldn't find fd !", set);
  }

  return idx >= 0;
}
