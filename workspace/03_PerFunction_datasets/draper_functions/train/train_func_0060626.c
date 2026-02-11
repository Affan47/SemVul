add_underscore(gchar *str)
{
  gchar *res;
  gchar *res2;
  gchar *ext;
  guint c = strlen(str);
  while (str[c] != '.') c--;
  res = g_strndup(str,c);
  ext = g_strdup(str+c);
  res2 = g_strconcat(res, "_", ext, NULL);
  g_free(str);
  g_free(ext);
  g_free(res);
  return res2;
}
