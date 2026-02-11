gst_gconf_render_bin_from_key (const gchar * key)
{
  GstElement *bin = NULL;
  gchar *value;

  value = gst_gconf_get_string (key);

  GST_LOG ("%s = %s", GST_STR_NULL (key), GST_STR_NULL (value));

  if (value) {
    GError *err = NULL;

    bin = gst_parse_bin_from_description (value, TRUE, &err);
    if (err) {
      GST_ERROR ("gconf: error creating bin '%s': %s", value, err->message);
      g_error_free (err);
    }

    g_free (value);
  }
  return bin;
}
