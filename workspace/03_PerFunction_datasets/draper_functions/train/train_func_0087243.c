get_buffer_level (RTPJitterBuffer * jbuf)
{
  GstBuffer *high_buf = NULL, *low_buf = NULL;
  guint64 level;
  GList *find;


  find = g_queue_peek_head_link (jbuf->packets);
  while (find) {
    high_buf = find->data;
    if (GST_BUFFER_TIMESTAMP (high_buf) != -1)
      break;

    high_buf = NULL;
    find = g_list_next (find);
  }

  find = g_queue_peek_tail_link (jbuf->packets);
  while (find) {
    low_buf = find->data;
    if (GST_BUFFER_TIMESTAMP (low_buf) != -1)
      break;

    low_buf = NULL;
    find = g_list_previous (find);
  }

  if (!high_buf || !low_buf || high_buf == low_buf) {
    level = 0;
  } else {
    guint64 high_ts, low_ts;

    high_ts = GST_BUFFER_TIMESTAMP (high_buf);
    low_ts = GST_BUFFER_TIMESTAMP (low_buf);

    if (high_ts > low_ts)
      level = high_ts - low_ts;
    else
      level = 0;

    GST_LOG_OBJECT (jbuf,
        "low %" GST_TIME_FORMAT " high %" GST_TIME_FORMAT " level %"
        G_GUINT64_FORMAT, GST_TIME_ARGS (low_ts), GST_TIME_ARGS (high_ts),
        level);
  }
  return level;
}
