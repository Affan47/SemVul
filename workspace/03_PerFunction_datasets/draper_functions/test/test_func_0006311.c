convert_encoding (GstSubParse * self, const gchar * str, gsize len,
    gsize * consumed)
{
  const gchar *encoding;
  GError *err = NULL;
  gchar *ret = NULL;

  *consumed = 0;


  if (self->detected_encoding) {
    ret =
        gst_convert_to_utf8 (str, len, self->detected_encoding, consumed, &err);

    if (!err)
      return ret;

    GST_WARNING_OBJECT (self, "could not convert string from '%s' to UTF-8: %s",
        self->detected_encoding, err->message);
    g_free (self->detected_encoding);
    self->detected_encoding = NULL;
    g_error_free (err);
  }


  if (self->valid_utf8) {
    if (g_utf8_validate (str, len, NULL)) {
      GST_LOG_OBJECT (self, "valid UTF-8, no conversion needed");
      *consumed = len;
      return g_strndup (str, len);
    }
    GST_INFO_OBJECT (self, "invalid UTF-8!");
    self->valid_utf8 = FALSE;
  }


  encoding = self->encoding;
  if (encoding == NULL || *encoding == '\0') {
    encoding = g_getenv ("GST_SUBTITLE_ENCODING");
  }
  if (encoding == NULL || *encoding == '\0') {


    if (g_get_charset (&encoding)) {
      encoding = "ISO-8859-15";
    }
  }

  ret = gst_convert_to_utf8 (str, len, encoding, consumed, &err);

  if (err) {
    GST_WARNING_OBJECT (self, "could not convert string from '%s' to UTF-8: %s",
        encoding, err->message);
    g_error_free (err);


    ret = gst_convert_to_utf8 (str, len, "ISO-8859-15", consumed, NULL);
  }

  GST_LOG_OBJECT (self,
      "successfully converted %" G_GSIZE_FORMAT " characters from %s to UTF-8"
      "%s", len, encoding, (err) ? " , using ISO-8859-15 as fallback" : "");

  return ret;
}
