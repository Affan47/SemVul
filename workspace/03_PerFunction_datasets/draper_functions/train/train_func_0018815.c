gst_vertigotv_transform (GstBaseTransform * trans, GstBuffer * in,
    GstBuffer * out)
{
  GstVertigoTV *filter = GST_VERTIGOTV (trans);
  guint32 *src, *dest, *p;
  guint32 v;
  gint x, y, ox, oy, i, width, height, area;
  GstFlowReturn ret = GST_FLOW_OK;
  GstClockTime timestamp, stream_time;

  timestamp = GST_BUFFER_TIMESTAMP (in);
  stream_time =
      gst_segment_to_stream_time (&trans->segment, GST_FORMAT_TIME, timestamp);

  GST_DEBUG_OBJECT (filter, "sync to %" GST_TIME_FORMAT,
      GST_TIME_ARGS (timestamp));

  if (GST_CLOCK_TIME_IS_VALID (stream_time))
    gst_object_sync_values (G_OBJECT (filter), stream_time);

  src = (guint32 *) GST_BUFFER_DATA (in);
  dest = (guint32 *) GST_BUFFER_DATA (out);

  GST_OBJECT_LOCK (filter);

  width = filter->width;
  height = filter->height;
  area = width * height;

  gst_vertigotv_set_parms (filter);
  p = filter->alt_buffer;

  for (y = height; y > 0; y--) {
    ox = filter->sx;
    oy = filter->sy;

    for (x = width; x > 0; x--) {
      i = (oy >> 16) * width + (ox >> 16);
      if (i < 0)
        i = 0;
      if (i >= area)
        i = area;

      v = filter->current_buffer[i] & 0xfcfcff;
      v = (v * 3) + ((*src++) & 0xfcfcff);

      *p++ = (v >> 2);
      ox += filter->dx;
      oy += filter->dy;
    }
    filter->sx -= filter->dy;
    filter->sy += filter->dx;
  }

  memcpy (dest, filter->alt_buffer, area * sizeof (guint32));

  p = filter->current_buffer;
  filter->current_buffer = filter->alt_buffer;
  filter->alt_buffer = p;
  GST_OBJECT_UNLOCK (filter);

  return ret;
}
