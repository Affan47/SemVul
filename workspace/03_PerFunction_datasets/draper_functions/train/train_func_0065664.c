replace_string (const gchar *str,
		const gchar *old,
		const gchar *new)
{
  gchar *new_str;

  if (strstr (str, old))
    {
      gchar **splitted_name;

      splitted_name = g_strsplit (str, old, -1);
      new_str = g_strjoinv (new, splitted_name);
      g_strfreev (splitted_name);
    }
  else
    new_str = g_strdup (str);

  return new_str;
}
