gst_file_sink_uri_set_uri (GstURIHandler * handler, const gchar * uri,
    GError ** error)
{
  gchar *location;
  gboolean ret;
  GstFileSink *sink = GST_FILE_SINK (handler);


  if (g_str_has_prefix (uri, "file://localhost/")) {
    char *tmp;


    tmp = g_strconcat ("file://", uri + 16, NULL);


    location = gst_uri_get_location (tmp);
    g_free (tmp);
  } else if (strcmp (uri, "file://") == 0) {


    gst_file_sink_set_location (sink, NULL, NULL);
    return TRUE;
  } else {
    location = gst_uri_get_location (uri);
  }

  if (!location) {
    g_set_error_literal (error, GST_URI_ERROR, GST_URI_ERROR_BAD_URI,
        "File URI without location");
    return FALSE;
  }

  if (!g_path_is_absolute (location)) {
    g_set_error_literal (error, GST_URI_ERROR, GST_URI_ERROR_BAD_URI,
        "File URI location must be an absolute path");
    g_free (location);
    return FALSE;
  }

  ret = gst_file_sink_set_location (sink, location, error);
  g_free (location);

  return ret;
}
