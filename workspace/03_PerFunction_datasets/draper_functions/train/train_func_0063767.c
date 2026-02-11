queue_deadlock_check (GstElement * queue, GstPlayBaseBin * play_base_bin)
{
  guint64 time, min_time;
  guint bytes;

  GST_DEBUG_OBJECT (play_base_bin, "overrun signal received from queue %s",
      GST_ELEMENT_NAME (queue));


  g_object_get (G_OBJECT (queue), "current-level-time", &time,
      "current-level-bytes", &bytes, "min-threshold-time", &min_time, NULL);

  GST_DEBUG_OBJECT (play_base_bin, "streaming mode, queue %s current %"
      GST_TIME_FORMAT ", min %" GST_TIME_FORMAT
      ", bytes %d", GST_ELEMENT_NAME (queue),
      GST_TIME_ARGS (time), GST_TIME_ARGS (min_time), bytes);


  if (bytes && time != 0 && time < min_time) {
    GST_DEBUG_OBJECT (play_base_bin,
        "possible deadlock found, removing byte limit");


    g_object_set (G_OBJECT (queue), "max-size-bytes", 0, NULL);


    g_signal_handlers_disconnect_by_func (queue,
        (gpointer) queue_deadlock_check, play_base_bin);
  } else {
    GST_DEBUG_OBJECT (play_base_bin, "no deadlock");
  }
}
