proxy_autoplug_factories_signal (GstElement * element, GstPad * pad,
    GstCaps * caps, GstURIDecodeBin * dec)
{
  GValueArray *result;

  g_signal_emit (dec,
      gst_uri_decode_bin_signals[SIGNAL_AUTOPLUG_FACTORIES], 0, pad, caps,
      &result);

  GST_DEBUG_OBJECT (dec, "autoplug-factories returned %p", result);

  return result;
}
