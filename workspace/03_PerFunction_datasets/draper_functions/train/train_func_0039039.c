plugin_init (GstPlugin * plugin)
{
  gboolean res;

  GST_DEBUG_CATEGORY_INIT (gst_encode_bin_debug, "encodebin", 0, "encoder bin");

#ifdef ENABLE_NLS
  GST_DEBUG ("binding text domain %s to locale dir %s", GETTEXT_PACKAGE,
      LOCALEDIR);
  bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
#endif


  res = gst_element_register (plugin, "encodebin", GST_RANK_NONE,
      GST_TYPE_ENCODE_BIN);

  return res;
}
