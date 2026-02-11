read_event (GstRtpGSTDepay * rtpgstdepay, guint type,
    GstBuffer * buf, guint * skip)
{
  guint offset, length;
  GstStructure *s;
  GstEvent *event;
  GstEventType etype;
  gchar *end;
  GstMapInfo map;

  gst_buffer_map (buf, &map, GST_MAP_READ);

  GST_DEBUG_OBJECT (rtpgstdepay, "buffer size %" G_GSIZE_FORMAT, map.size);

  if (!read_length (rtpgstdepay, map.data, map.size, &length, &offset))
    goto too_small;

  GST_DEBUG_OBJECT (rtpgstdepay, "parsing event %s", &map.data[offset]);


  s = gst_structure_from_string ((gchar *) & map.data[offset], &end);
  gst_buffer_unmap (buf, &map);

  if (s == NULL)
    goto parse_failed;

  switch (type) {
    case 1:
      etype = GST_EVENT_TAG;
      break;
    case 2:
      etype = GST_EVENT_CUSTOM_DOWNSTREAM;
      break;
    case 3:
      etype = GST_EVENT_CUSTOM_BOTH;
      break;
    case 4:
      etype = GST_EVENT_STREAM_START;
      break;
    default:
      goto unknown_event;
  }
  event = gst_event_new_custom (etype, s);

  *skip = length + offset;

  return event;

too_small:
  {
    GST_ELEMENT_WARNING (rtpgstdepay, STREAM, DECODE,
        ("Buffer too small."), (NULL));
    gst_buffer_unmap (buf, &map);
    return NULL;
  }
parse_failed:
  {
    GST_WARNING_OBJECT (rtpgstdepay, "could not parse event");
    return NULL;
  }
unknown_event:
  {
    GST_DEBUG_OBJECT (rtpgstdepay, "unknown event type");
    gst_structure_free (s);
    return NULL;
  }
}
