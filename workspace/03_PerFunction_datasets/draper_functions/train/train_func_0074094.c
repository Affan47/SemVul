gst_decode_bin_dispose (GObject * object)
{
  GstDecodeBin *decode_bin;

  decode_bin = GST_DECODE_BIN (object);

  if (decode_bin->factories)
    gst_plugin_feature_list_free (decode_bin->factories);
  decode_bin->factories = NULL;

  if (decode_bin->decode_chain)
    gst_decode_chain_free (decode_bin->decode_chain);
  decode_bin->decode_chain = NULL;

  if (decode_bin->caps)
    gst_caps_unref (decode_bin->caps);
  decode_bin->caps = NULL;

  g_free (decode_bin->encoding);
  decode_bin->encoding = NULL;

  g_list_free (decode_bin->subtitles);
  decode_bin->subtitles = NULL;

  G_OBJECT_CLASS (parent_class)->dispose (object);
}
