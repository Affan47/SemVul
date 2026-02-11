gst_pad_is_active (GstPad * pad)
{
  gboolean result = FALSE;

  g_return_val_if_fail (GST_IS_PAD (pad), FALSE);

  GST_OBJECT_LOCK (pad);
  result = GST_PAD_MODE_ACTIVATE (GST_PAD_ACTIVATE_MODE (pad));
  GST_OBJECT_UNLOCK (pad);

  return result;
}
