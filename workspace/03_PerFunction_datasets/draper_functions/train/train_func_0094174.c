gst_revtv_transform (GstBaseTransform * trans, GstBuffer * in, GstBuffer * out)
{
  GstRevTV *filter = GST_REVTV (trans);
  guint32 *src, *dest;
  gint width, height;
  guint32 *nsrc;
  gint y, x, R, G, B, yval;
  GstFlowReturn ret = GST_FLOW_OK;
  gint linespace, vscale;
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


  memset (dest, 0, width * height * sizeof (guint32));

  linespace = filter->linespace;
  vscale = filter->vscale;


  for (y = 0; y < height; y += linespace) {
    for (x = 0; x <= width; x++) {
      nsrc = src + (y * width) + x;


      R = ((*nsrc) & 0xff0000) >> (16 - 1);
      G = ((*nsrc) & 0xff00) >> (8 - 2);
      B = (*nsrc) & 0xff;

      yval = y - ((short) (R + G + B) / vscale);

      if (yval > 0) {
        dest[x + (yval * width)] = THE_COLOR;
      }
    }
  }
  GST_OBJECT_UNLOCK (filter);

  return ret;
}
