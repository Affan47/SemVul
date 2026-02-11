plugin_init (GstPlugin * plugin)
{
  gst_riff_init ();

#ifdef ENABLE_NLS
  setlocale (LC_ALL, "");
  bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
#endif

  if (!gst_element_register (plugin, "avidemux", GST_RANK_PRIMARY,
          GST_TYPE_AVI_DEMUX) ||
      !gst_element_register (plugin, "avimux", GST_RANK_PRIMARY,
          GST_TYPE_AVI_MUX) ||
      !gst_element_register (plugin, "avisubtitle", GST_RANK_PRIMARY,
          GST_TYPE_AVI_SUBTITLE)) {
    return FALSE;
  }

  return TRUE;
}
