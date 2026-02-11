get_line_for_text (const gchar * path, const gchar * msgid)
{
  gchar *content, *str_found, *i, *escaped;
  int result;

  content = NULL;
  result = 1;
  escaped = g_markup_escape_text (msgid, -1);

  if (!g_file_get_contents (path, &content, NULL, NULL))
    goto out;

  i = content;
  while ((str_found = g_strstr_len (i, -1, escaped)))
    {
      gchar c;

      i = str_found + strlen (escaped);
      c = *i;
      if (!isalpha (c) &&
          !isalpha (*(str_found - 1)) && !(c == ':') && !(c == '_'))
        break;
    }
  if (!str_found)
    goto out;

  for (i = content; i < str_found; i++)
    if (*i == '\n')
      result++;

out:
  g_free (content);
  g_free (escaped);

  return result;
}
