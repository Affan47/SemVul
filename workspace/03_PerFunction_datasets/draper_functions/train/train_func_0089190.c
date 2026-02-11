gst_linsys_sdi_sink_dispose (GObject * object)
{
  GstLinsysSdiSink *linsyssdisink;

  g_return_if_fail (GST_IS_LINSYS_SDI_SINK (object));
  linsyssdisink = GST_LINSYS_SDI_SINK (object);


  g_free (linsyssdisink->device);
  linsyssdisink->device = NULL;

  G_OBJECT_CLASS (parent_class)->dispose (object);
}
