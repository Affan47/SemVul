g_utf8_strndup(gchar* utf8text, gint n)
{
  gchar* result;

  gint len = g_utf8_strlen(utf8text, -1);

  if( n < len && n > 0 )
    len = n;

  result = g_strndup(utf8text, g_utf8_offset_to_pointer(utf8text, len) - utf8text);

  return result;
}
