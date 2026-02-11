clutter_gst_source_prepare (GSource * source, gint * timeout)
{
  ClutterGstSource *gst_source = (ClutterGstSource *) source;

  GST_DEBUG_OBJECT (gst_source->sink, "Preparing GSource");

  *timeout = -1;

  return gst_source->buffer != NULL;
}
