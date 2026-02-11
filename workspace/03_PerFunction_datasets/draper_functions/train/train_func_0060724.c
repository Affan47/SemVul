gst_value_deserialize_buffer (GValue * dest, const gchar * s)
{
  GstBuffer *buffer;
  gint len;
  gchar ts[3];
  guint8 *data;
  gint i;

  len = strlen (s);
  if (len & 1)
    goto wrong_length;

  buffer = gst_buffer_new_and_alloc (len / 2);
  data = GST_BUFFER_DATA (buffer);
  for (i = 0; i < len / 2; i++) {
    if (!isxdigit ((int) s[i * 2]) || !isxdigit ((int) s[i * 2 + 1]))
      goto wrong_char;

    ts[0] = s[i * 2 + 0];
    ts[1] = s[i * 2 + 1];
    ts[2] = 0;

    data[i] = (guint8) strtoul (ts, NULL, 16);
  }

  gst_value_take_buffer (dest, buffer);

  return TRUE;


wrong_length:
  {
    return FALSE;
  }
wrong_char:
  {
    gst_buffer_unref (buffer);
    return FALSE;
  }
}
