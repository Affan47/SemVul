gst_pb_utils_get_encoder_description (const GstCaps * caps)
{
  gchar *str, *ret;
  GstCaps *tmp;

  g_return_val_if_fail (caps != NULL, NULL);
  g_return_val_if_fail (GST_IS_CAPS (caps), NULL);
  tmp = copy_and_clean_caps (caps);
  g_return_val_if_fail (gst_caps_is_fixed (tmp), NULL);


  if (caps_are_rtp_caps (tmp, "video", &str)) {
    ret = g_strdup_printf (_("%s video RTP payloader"), str);
  } else if (caps_are_rtp_caps (tmp, "audio", &str)) {
    ret = g_strdup_printf (_("%s audio RTP payloader"), str);
  } else if (caps_are_rtp_caps (tmp, "application", &str)) {
    ret = g_strdup_printf (_("%s RTP payloader"), str);
  } else {
    const FormatInfo *info;

    str = gst_pb_utils_get_codec_description (tmp);
    info = find_format_info (tmp);
    if (info != NULL && (info->flags & FLAG_CONTAINER) != 0) {
      ret = g_strdup_printf (_("%s muxer"), str);
    } else {
      ret = g_strdup_printf (_("%s encoder"), str);
    }
  }

  g_free (str);
  gst_caps_unref (tmp);

  return ret;
}
