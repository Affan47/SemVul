insert_string_link_codepoints (GucharmapCharmap *charmap,
                               GtkTextBuffer *buffer,
                               GtkTextIter *iter,
                               const gchar *str)
{
  const gchar *p1, *p2;

  p1 = str;
  for (;;)
    {
      p2 = find_codepoint (p1);
      if (p2 != NULL)
        {
          gunichar uc;
          gtk_text_buffer_insert (buffer, iter, p1, p2 - p1);
          uc = strtoul (p2, (gchar **) &p1, 16);
          insert_codepoint (charmap, buffer, iter, uc);
        }
      else
        {
          gtk_text_buffer_insert (buffer, iter, p1, -1);
          break;
        }
    }
}
