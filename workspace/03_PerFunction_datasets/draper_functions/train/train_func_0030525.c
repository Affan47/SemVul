gst_jpeg_parse_set_new_caps (GstJpegParse * parse, gboolean header_ok)
{
  GstCaps *caps;
  gboolean res;

  GST_DEBUG_OBJECT (parse, "setting caps on srcpad (hdr_ok=%d, have_fps=%d)",
      header_ok, parse->priv->has_fps);

  caps = gst_caps_new_simple ("image/jpeg",
      "parsed", G_TYPE_BOOLEAN, TRUE, NULL);

  if (header_ok == TRUE) {
    gst_caps_set_simple (caps,
        "format", G_TYPE_STRING, parse->priv->format,
        "interlaced", G_TYPE_BOOLEAN, parse->priv->interlaced,
        "width", G_TYPE_INT, parse->priv->width,
        "height", G_TYPE_INT, parse->priv->height, NULL);
  }

  if (parse->priv->has_fps == TRUE) {

    gst_caps_set_simple (caps, "framerate", GST_TYPE_FRACTION,
        parse->priv->framerate_numerator,
        parse->priv->framerate_denominator, NULL);

    if (!GST_CLOCK_TIME_IS_VALID (parse->priv->duration)
        && parse->priv->framerate_numerator != 0) {
      parse->priv->duration = gst_util_uint64_scale_int (GST_SECOND,
          parse->priv->framerate_denominator, parse->priv->framerate_numerator);
    }
  } else {

    parse->priv->duration = GST_CLOCK_TIME_NONE;
    gst_caps_set_simple (caps, "framerate", GST_TYPE_FRACTION, 1, 1, NULL);
  }

  GST_DEBUG_OBJECT (parse,
      "setting downstream caps on %s:%s to %" GST_PTR_FORMAT,
      GST_DEBUG_PAD_NAME (parse->priv->srcpad), caps);
  res = gst_pad_set_caps (parse->priv->srcpad, caps);
  gst_caps_unref (caps);

  return res;

}
