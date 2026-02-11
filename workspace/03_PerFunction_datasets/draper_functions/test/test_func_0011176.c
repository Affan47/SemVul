update_log_pane (int section)
{
  GtkTextBuffer *buffer = gtk_text_view_get_buffer (texts[section].view);
  GtkTextIter start, end;

  gtk_text_buffer_get_start_iter (buffer, &start);
  gtk_text_buffer_get_end_iter (buffer, &end);
  gtk_text_buffer_delete (buffer, &start, &end);

  const char *const *log = xine_get_log (xine, section);

  if (log)
  {
    int j = 0;
    while (log[j])
      ++j;
    for (--j; j >= 0; --j)
      add_log_line (buffer, &end, log[j], -1);
    scroll_to_bottom (section);
  }
}
