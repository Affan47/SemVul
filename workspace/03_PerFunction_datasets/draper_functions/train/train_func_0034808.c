gst_poll_fd_can_read (const GstPoll * set, GstPollFD * fd)
{
  gboolean res = FALSE;

  g_return_val_if_fail (set != NULL, FALSE);
  g_return_val_if_fail (fd != NULL, FALSE);
  g_return_val_if_fail (fd->fd >= 0, FALSE);

  g_mutex_lock (set->lock);

  res = gst_poll_fd_can_read_unlocked (set, fd);

  g_mutex_unlock (set->lock);

  return res;
}
