gst_pad_get_direction (GstPad * pad)
{
  GstPadDirection result;


  g_return_val_if_fail (GST_IS_PAD (pad), GST_PAD_UNKNOWN);

  result = GST_PAD_DIRECTION (pad);

  return result;
}
