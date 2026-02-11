strnsplit (const gchar *string,
           gsize length,
           gchar delimiter)
{
  GSList *string_list = NULL, *slist;
  gchar **str_array, *s;
  guint n = 0;
  const gchar *remainder;
  const gchar *end;

  g_return_val_if_fail (string != NULL, NULL);
  g_return_val_if_fail (delimiter != '\0', NULL);

  end = string + length;
  remainder = string;
  s = memchr (remainder, delimiter, end - remainder);
  if (s)
    {
      while (s)
        {
          gsize len;

          len = s - remainder;
          string_list = g_slist_prepend (string_list,
                                         g_strndup (remainder, len));
          n++;
          remainder = s + 1;
          s = memchr (remainder, delimiter, end - remainder);
        }
    }
  if (*string)
    {
      n++;
      string_list = g_slist_prepend (string_list, g_strndup (remainder, end - remainder));
    }

  str_array = g_new (gchar*, n + 1);

  str_array[n--] = NULL;
  for (slist = string_list; slist; slist = slist->next)
    str_array[n--] = slist->data;

  g_slist_free (string_list);

  return str_array;
}
