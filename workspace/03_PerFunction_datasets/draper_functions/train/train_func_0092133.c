util_remove_comment (gchar * str)
{
  gchar *p = str;
  g_assert (str);
  while (*p && *p != ';')
	p++;
  *p = '\0';
}
