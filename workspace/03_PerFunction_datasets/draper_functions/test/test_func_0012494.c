gst_dp_dump_byte_array (guint8 * array, guint length)
{
  int i;
  int n = 8;
  gchar *line = g_malloc0 (3 * n + 1);

  GST_LOG ("dumping byte array of length %d", length);
  for (i = 0; i < length; ++i) {
    g_sprintf (line + 3 * (i % n), "%02x ", array[i]);
    if (i % n == (n - 1)) {
      GST_LOG ("%03d: %s", i - (n - 1), line);
    }
  }
  if (i % n != 0) {
    GST_LOG ("%03d: %s", (i / n) * n, line);
  }
  g_free (line);
}
