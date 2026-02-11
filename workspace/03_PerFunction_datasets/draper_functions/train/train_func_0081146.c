gst_cmml_tag_stream_finalize (GObject * object)
{
  GstCmmlTagStream *stream = GST_CMML_TAG_STREAM (object);

  g_free (stream->timebase);
  g_free (stream->utc);
  if (stream->imports)
    g_value_array_free (stream->imports);

  if (G_OBJECT_CLASS (gst_cmml_tag_stream_parent_class)->finalize)
    G_OBJECT_CLASS (gst_cmml_tag_stream_parent_class)->finalize (object);
}
