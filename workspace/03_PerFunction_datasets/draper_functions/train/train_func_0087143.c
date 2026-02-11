gst_poll_remove_fd (GstPoll * set, GstPollFD * fd)
{
  gint idx;

  g_return_val_if_fail (set != NULL, FALSE);
  g_return_val_if_fail (fd != NULL, FALSE);
  g_return_val_if_fail (fd->fd >= 0, FALSE);


  GST_DEBUG ("%p: fd (fd:%d, idx:%d)", set, fd->fd, fd->idx);

  g_mutex_lock (&set->lock);


  idx = find_index (set->fds, fd);
  if (idx >= 0) {
#ifdef G_OS_WIN32
    gst_poll_free_winsock_event (set, idx);
    g_array_remove_index_fast (set->events, idx);
#endif


    g_array_remove_index_fast (set->fds, idx);


    fd->idx = -1;
    MARK_REBUILD (set);
  } else {
    GST_WARNING ("%p: couldn't find fd !", set);
  }

  g_mutex_unlock (&set->lock);

  return idx >= 0;
}
