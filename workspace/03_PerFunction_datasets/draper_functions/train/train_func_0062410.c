subrip_unescape_formatting (gchar * txt)
{
  gchar *pos;

  for (pos = txt; pos != NULL && *pos != '\0'; ++pos) {
    if (g_ascii_strncasecmp (pos, "&lt;u&gt;", 9) == 0 ||
        g_ascii_strncasecmp (pos, "&lt;i&gt;", 9) == 0 ||
        g_ascii_strncasecmp (pos, "&lt;b&gt;", 9) == 0) {
      pos[0] = '<';
      pos[1] = g_ascii_tolower (pos[4]);
      pos[2] = '>';

      memmove (pos + 3, pos + 9, strlen (pos + 9) + 1);
      pos += 2;
    }
  }

  for (pos = txt; pos != NULL && *pos != '\0'; ++pos) {
    if (g_ascii_strncasecmp (pos, "&lt;/u&gt;", 10) == 0 ||
        g_ascii_strncasecmp (pos, "&lt;/i&gt;", 10) == 0 ||
        g_ascii_strncasecmp (pos, "&lt;/b&gt;", 10) == 0) {
      pos[0] = '<';
      pos[1] = '/';
      pos[2] = g_ascii_tolower (pos[5]);
      pos[3] = '>';

      memmove (pos + 4, pos + 10, strlen (pos + 10) + 1);
      pos += 3;
    }
  }
}
