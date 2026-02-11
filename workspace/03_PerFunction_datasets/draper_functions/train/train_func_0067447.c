gst_base_src_negotiate (GstBaseSrc * basesrc)
{
  GstBaseSrcClass *bclass;
  gboolean result;

  bclass = GST_BASE_SRC_GET_CLASS (basesrc);

  GST_DEBUG_OBJECT (basesrc, "starting negotiation");

  if (G_LIKELY (bclass->negotiate))
    result = bclass->negotiate (basesrc);
  else
    result = TRUE;

  if (G_LIKELY (result)) {
    GstCaps *caps;

    caps = gst_pad_get_current_caps (basesrc->srcpad);

    result = gst_base_src_prepare_allocation (basesrc, caps);

    if (caps)
      gst_caps_unref (caps);
  }
  return result;
}
