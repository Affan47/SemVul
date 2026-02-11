gst_multi_fd_sink_recover_client (GstMultiFdSink * sink, GstTCPClient * client)
{
  gint newbufpos;

  GST_WARNING_OBJECT (sink,
      "[fd %5d] client %p is lagging at %d, recover using policy %d",
      client->fd.fd, client, client->bufpos, sink->recover_policy);

  switch (sink->recover_policy) {
    case GST_RECOVER_POLICY_NONE:


      newbufpos = client->bufpos;
      break;
    case GST_RECOVER_POLICY_RESYNC_LATEST:

      newbufpos = -1;
      break;
    case GST_RECOVER_POLICY_RESYNC_SOFT_LIMIT:

      newbufpos = get_buffers_max (sink, sink->units_soft_max);
      break;
    case GST_RECOVER_POLICY_RESYNC_KEYFRAME:


      newbufpos = MIN (sink->bufqueue->len - 1,
          get_buffers_max (sink, sink->units_soft_max) - 1);

      while (newbufpos >= 0) {
        GstBuffer *buf;

        buf = g_array_index (sink->bufqueue, GstBuffer *, newbufpos);
        if (is_sync_frame (sink, buf)) {

          break;
        }
        newbufpos--;
      }
      break;
    default:

      newbufpos = get_buffers_max (sink, sink->units_soft_max);
      break;
  }
  return newbufpos;
}
