gst_base_sink_pad_fixate (GstPad * pad, GstCaps * caps)
{
  GstBaseSinkClass *bclass;
  GstBaseSink *bsink;

  bsink = GST_BASE_SINK (gst_pad_get_parent (pad));
  bclass = GST_BASE_SINK_GET_CLASS (bsink);

  if (bclass->fixate)
    bclass->fixate (bsink, caps);

  gst_object_unref (bsink);
}
