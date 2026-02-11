strip_trailing_newlines (gchar * txt)
{
  if (txt) {
    guint len;

    len = strlen (txt);
    while (len > 1 && txt[len - 1] == '\n') {
      txt[len - 1] = '\0';
      --len;
    }
  }
}
