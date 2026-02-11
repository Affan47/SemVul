gst_decode_pad_new (GstDecodeBin * dbin, GstPad * pad, GstDecodeChain * chain)
{
  GstDecodePad *dpad;
  GstPadTemplate *pad_tmpl;

  GST_DEBUG_OBJECT (dbin, "making new decodepad");
  pad_tmpl = gst_static_pad_template_get (&decoder_bin_src_template);
  dpad =
      g_object_new (GST_TYPE_DECODE_PAD, "direction", GST_PAD_DIRECTION (pad),
      "template", pad_tmpl, NULL);
  gst_ghost_pad_construct (GST_GHOST_PAD_CAST (dpad));
  gst_ghost_pad_set_target (GST_GHOST_PAD_CAST (dpad), pad);
  dpad->chain = chain;
  dpad->dbin = dbin;
  gst_object_unref (pad_tmpl);

  return dpad;
}
