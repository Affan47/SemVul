gst_queue_handle_src_query (GstPad * pad, GstQuery * query)
{
  GstQueue *queue = GST_QUEUE (gst_pad_get_parent (pad));
  GstPad *peer;
  gboolean res;

  if (G_UNLIKELY (queue == NULL))
    return FALSE;

  if (!(peer = gst_pad_get_peer (queue->sinkpad))) {
    gst_object_unref (queue);
    return FALSE;
  }

  res = gst_pad_query (peer, query);
  gst_object_unref (peer);
  if (!res) {
    gst_object_unref (queue);
    return FALSE;
  }

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_POSITION:
    {
      gint64 peer_pos;
      GstFormat format;


      gst_query_parse_position (query, &format, &peer_pos);


      switch (format) {
        case GST_FORMAT_BYTES:
          peer_pos -= queue->cur_level.bytes;
          break;
        case GST_FORMAT_TIME:
          peer_pos -= queue->cur_level.time;
          break;
        default:
          GST_DEBUG_OBJECT (queue, "Can't adjust query in %s format, don't "
              "know how to adjust value", gst_format_get_name (format));
          return TRUE;
      }

      gst_query_set_position (query, format, peer_pos);
      break;
    }
    case GST_QUERY_LATENCY:
    {
      gboolean live;
      GstClockTime min, max;

      gst_query_parse_latency (query, &live, &min, &max);


      if (queue->max_size.time > 0 && max != -1)
        max += queue->max_size.time;
      else
        max = -1;


      if (queue->min_threshold.time > 0 && min != -1)
        min += queue->min_threshold.time;

      gst_query_set_latency (query, live, min, max);
      break;
    }
    default:

      break;
  }

  gst_object_unref (queue);
  return TRUE;
}
