gst_system_clock_add_wakeup (GstSystemClock * sysclock)
{

  if (sysclock->priv->wakeup_count == 0) {
    GST_CAT_DEBUG (GST_CAT_CLOCK, "writing control");
    while (!gst_poll_write_control (sysclock->priv->timer)) {
      if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
        g_warning
            ("gstsystemclock: write control failed in wakeup_async, trying again: %d:%s\n",
            errno, g_strerror (errno));
      } else {
        g_critical
            ("gstsystemclock: write control failed in wakeup_async: %d:%s\n",
            errno, g_strerror (errno));
        return;
      }
    }
  }
  sysclock->priv->wakeup_count++;
  GST_CAT_DEBUG (GST_CAT_CLOCK, "wakeup count %d",
      sysclock->priv->wakeup_count);
}
