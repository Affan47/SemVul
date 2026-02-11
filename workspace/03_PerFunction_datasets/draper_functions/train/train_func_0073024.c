are_final_caps (GstDecodeBin * dbin, GstCaps * caps)
{
  gboolean res;

  GST_LOG_OBJECT (dbin, "Checking with caps %" GST_PTR_FORMAT, caps);


  GST_OBJECT_LOCK (dbin);
  res = gst_caps_can_intersect (dbin->caps, caps);
  GST_OBJECT_UNLOCK (dbin);

  GST_LOG_OBJECT (dbin, "Caps are %sfinal caps", res ? "" : "not ");

  return res;
}
