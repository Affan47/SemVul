gst_decode_pad_activate (GstDecodePad * dpad, GstDecodeChain * chain)
{
  g_return_if_fail (chain != NULL);

  dpad->chain = chain;
  gst_pad_set_active (GST_PAD_CAST (dpad), TRUE);
  gst_decode_pad_set_blocked (dpad, TRUE);
  gst_decode_pad_add_drained_check (dpad);
}
