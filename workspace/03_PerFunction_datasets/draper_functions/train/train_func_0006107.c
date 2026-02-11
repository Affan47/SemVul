writeShort (short val )
{
    gchar *buf = g_strdup_printf("%d", val);
    if (buf) {
        writeString(buf);
        g_free(buf);
    }
  return *this;
}
