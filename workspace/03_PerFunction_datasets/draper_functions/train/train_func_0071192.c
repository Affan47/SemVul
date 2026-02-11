gst_rtsp_url_decode_path_components (const GstRTSPUrl * url)
{
  gchar **ret;
  guint i;

  g_return_val_if_fail (url != NULL, NULL);
  g_return_val_if_fail (url->abspath != NULL, NULL);

  ret = g_strsplit (url->abspath, "/", -1);

  for (i = 0; ret[i]; i++)
    unescape_path_component (ret[i]);

  return ret;
}
