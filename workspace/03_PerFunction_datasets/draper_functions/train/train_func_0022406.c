tab_to (GString *string, gint position)
{
  gchar *p;
  gint   curcount = 0;
  gint   i;

  p = strrchr (string->str, '\n');
  if (!p)
    {
      p = string->str;
      curcount++;
    }
  while (p && *p != '\0')
    {
      curcount++;
      p++;
    }

  if (curcount > position && position != 0)
    {
      g_warning ("%s tab overflow %i>%i", G_STRLOC, curcount, position);
    }
  else
    {
      for (i = 0; i <= position - curcount; i++)
        string = g_string_append (string, " ");
    }
  return string;
}
