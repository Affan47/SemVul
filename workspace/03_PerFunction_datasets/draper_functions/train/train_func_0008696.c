filter_buffer (LogviewWindow *logview, gint start_line)
{
  GtkTextBuffer *buffer;
  GtkTextIter start, *end;
  gchar* text;
  GList* cur_filter;
  gboolean matched;
  int lines, i;

  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (logview->priv->text_view));
  lines = gtk_text_buffer_get_line_count (buffer);

  for (i = start_line; i < lines; i++) {
    matched = FALSE;

    gtk_text_buffer_get_iter_at_line (buffer, &start, i);
    end = gtk_text_iter_copy (&start);
    gtk_text_iter_forward_line (end);

    text = gtk_text_buffer_get_text (buffer, &start, end, TRUE);

    for (cur_filter = logview->priv->active_filters; cur_filter != NULL;
         cur_filter = g_list_next (cur_filter))
    {
      if (logview_filter_filter (LOGVIEW_FILTER (cur_filter->data), text)) {
        gtk_text_buffer_apply_tag (buffer,
                                   logview_filter_get_tag (LOGVIEW_FILTER (cur_filter->data)),
                                   &start, end);
        matched = TRUE;
      }
    }

    g_free (text);

    if (!matched && logview->priv->matches_only) {
      gtk_text_buffer_apply_tag_by_name (buffer,
                                         "invisible-filter",
                                         &start, end);
    } else {
      gtk_text_buffer_remove_tag_by_name (buffer,
                                          "invisible-filter",
                                          &start, end);
    }

    gtk_text_iter_free (end);
  }
}
