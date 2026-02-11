parse_insert_string_field (guint8 encoding, gchar * data, gint data_size,
    GArray * fields)
{
  gchar *field = NULL;

  switch (encoding) {
    case ID3V2_ENCODING_UTF16:
    case ID3V2_ENCODING_UTF16BE:
    {
      const gchar *in_encode;

      if (encoding == ID3V2_ENCODING_UTF16)
        in_encode = utf16enc;
      else
        in_encode = utf16beenc;


      while (data_size > 2 && find_utf16_bom (data, &in_encode)) {
        data += 2;
        data_size -= 2;
      }

      field = g_convert (data, data_size, "UTF-8", in_encode, NULL, NULL, NULL);

      if (field == NULL || g_utf8_validate (field, -1, NULL) == FALSE) {

        if (in_encode == utf16beenc)
          field = g_convert (data, data_size, "UTF-8", utf16leenc,
              NULL, NULL, NULL);
      }
    }

      break;
    case ID3V2_ENCODING_ISO8859:
      if (g_utf8_validate (data, data_size, NULL))
        field = g_strndup (data, data_size);
      else


        field = string_utf8_dup (data, data_size);
      break;
    default:
      field = g_strndup (data, data_size);
      break;
  }

  if (field) {
    if (g_utf8_validate (field, -1, NULL)) {
      g_array_append_val (fields, field);
      return;
    }

    GST_DEBUG ("%s was bad UTF-8 after conversion from encoding %d. Ignoring",
        field, encoding);
    g_free (field);
  }
}
