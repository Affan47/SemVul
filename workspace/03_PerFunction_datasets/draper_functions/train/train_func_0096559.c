gst_gdk_pixbuf_chain (GstPad * pad, GstBuffer * buf)
{
  GstGdkPixbuf *filter;
  GstFlowReturn ret = GST_FLOW_OK;
  GError *error = NULL;
  GstClockTime timestamp;
  guint8 *data;
  guint size;

  filter = GST_GDK_PIXBUF (gst_pad_get_parent (pad));

  timestamp = GST_BUFFER_TIMESTAMP (buf);

  if (GST_CLOCK_TIME_IS_VALID (timestamp))
    filter->last_timestamp = timestamp;

  GST_LOG_OBJECT (filter, "buffer with ts: %" GST_TIME_FORMAT,
      GST_TIME_ARGS (timestamp));

  if (filter->pixbuf_loader == NULL)
    filter->pixbuf_loader = gdk_pixbuf_loader_new ();

  data = GST_BUFFER_DATA (buf);
  size = GST_BUFFER_SIZE (buf);

  GST_LOG_OBJECT (filter, "Writing buffer size %d", size);
  if (!gdk_pixbuf_loader_write (filter->pixbuf_loader, data, size, &error))
    goto error;


  if (filter->framerate_numerator != 0) {
    gdk_pixbuf_loader_close (filter->pixbuf_loader, NULL);
    ret = gst_gdk_pixbuf_flush (filter);
    g_object_unref (filter->pixbuf_loader);
    filter->pixbuf_loader = NULL;
  }

  gst_buffer_unref (buf);
  gst_object_unref (filter);

  return ret;


error:
  {
    GST_ELEMENT_ERROR (filter, STREAM, DECODE, (NULL),
        ("gdk_pixbuf_loader_write error: %s", error->message));
    g_error_free (error);
    gst_buffer_unref (buf);
    gst_object_unref (filter);
    return GST_FLOW_ERROR;
  }
}
