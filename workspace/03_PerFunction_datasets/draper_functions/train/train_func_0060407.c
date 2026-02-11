kill_tracknumber(const gchar *string)
{


  gchar *tmp;

  if (strlen(string) < 4)
    return g_strdup(string);
  if (g_ascii_isdigit(string[0]) &&
      g_ascii_isdigit(string[1]) &&
      !g_ascii_isdigit(string[2]) &&
      string[2] != '\'') {
    tmp = g_strdup(string+2);
    g_strstrip(tmp);
    return tmp;
  }
  return g_strdup(string);
}
