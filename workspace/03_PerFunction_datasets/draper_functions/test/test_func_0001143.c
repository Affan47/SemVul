_bufSetText(const gchar *text, GtkTextTag *tag, gboolean error)
{
  GtkTextIter iter;

  gtk_text_buffer_get_end_iter(pyTextBuffer, &iter);
  if (!error)
    gtk_text_buffer_insert_with_tags(pyTextBuffer, &iter, text, -1, tag, NULL);
  else
    gtk_text_buffer_insert_with_tags(pyTextBuffer, &iter, text, -1, tag, errorTag, NULL);
}
