mxf_utf16_to_utf8 (const guint8 * data, guint size)
{
  gchar *ret;
  GError *error = NULL;

  ret =
      g_convert ((const gchar *) data, size, "UTF-8", "UTF-16BE", NULL, NULL,
      &error);

  if (ret == NULL) {
    GST_WARNING ("UTF-16-BE to UTF-8 conversion failed: %s", error->message);
    g_error_free (error);
    return NULL;
  }

  return ret;
}
