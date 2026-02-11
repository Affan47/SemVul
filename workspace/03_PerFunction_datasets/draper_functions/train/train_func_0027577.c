alignPrint(GString *str, const gchar* value, int ln, gchar *pad)
{
  gchar *sp;
  gchar *tmp;

  if (g_utf8_strlen(value, -1) <= ln)
    {
      g_string_append_printf(str, "%s%s", pad, value);
      return;
    }

  sp = g_utf8_strrchr(value, ln, ' ');
  g_return_if_fail(sp);

  tmp = g_strndup(value, (gsize)(sp - value));
  g_string_append_printf(str, "%s%s\n", pad, tmp);
  g_free(tmp);
  alignPrint(str, sp + 1, ln, pad);
}
