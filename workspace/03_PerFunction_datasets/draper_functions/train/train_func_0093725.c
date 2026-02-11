gst_file_src_uri_set_uri (GstURIHandler * handler, const gchar * uri)
{
  gchar *location, *hostname = NULL;
  gboolean ret = FALSE;
  GstFileSrc *src = GST_FILE_SRC (handler);
  GError *error = NULL;

  if (strcmp (uri, "file://") == 0) {


    gst_file_src_set_location (src, NULL);
    return TRUE;
  }

  location = g_filename_from_uri (uri, &hostname, &error);

  if (!location || error) {
    if (error) {
      GST_WARNING_OBJECT (src, "Invalid URI '%s' for filesrc: %s", uri,
          error->message);
      g_error_free (error);
    } else {
      GST_WARNING_OBJECT (src, "Invalid URI '%s' for filesrc", uri);
    }
    goto beach;
  }

  if ((hostname) && (strcmp (hostname, "localhost"))) {

    GST_WARNING_OBJECT (src, "Invalid hostname '%s' for filesrc", hostname);
    goto beach;
  }
#ifdef G_OS_WIN32


  if (location[0] == '\\' && location[1] == '\\' && location[2] == '\\')
    g_memmove (location, location + 1, strlen (location + 1) + 1);
#endif

  ret = gst_file_src_set_location (src, location);

beach:
  if (location)
    g_free (location);
  if (hostname)
    g_free (hostname);

  return ret;
}
