gst_pad_get_caps_reffed (GstPad * pad)
{
  GstCaps *result = NULL;

  g_return_val_if_fail (GST_IS_PAD (pad), NULL);

  GST_OBJECT_LOCK (pad);

  GST_CAT_DEBUG_OBJECT (GST_CAT_CAPS, pad, "get pad caps");

  result = gst_pad_get_caps_unlocked (pad);

  GST_OBJECT_UNLOCK (pad);

  return result;
}
