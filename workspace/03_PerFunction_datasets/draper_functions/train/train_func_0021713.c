gst_missing_decoder_installer_detail_new (const GstCaps * decode_caps)
{
  GstCaps *caps;
  gchar *detail_str, *caps_str, *desc;

  g_return_val_if_fail (decode_caps != NULL, NULL);
  g_return_val_if_fail (GST_IS_CAPS (decode_caps), NULL);
  g_return_val_if_fail (!gst_caps_is_any (decode_caps), NULL);
  g_return_val_if_fail (!gst_caps_is_empty (decode_caps), NULL);
  g_return_val_if_fail (gst_caps_is_fixed (decode_caps), NULL);

  desc = gst_pb_utils_get_decoder_description (decode_caps);
  caps = copy_and_clean_caps (decode_caps);
  caps_str = gst_caps_to_string (caps);
  detail_str = gst_installer_detail_new (desc, "decoder", caps_str);
  g_free (caps_str);
  gst_caps_unref (caps);

  return detail_str;
}
