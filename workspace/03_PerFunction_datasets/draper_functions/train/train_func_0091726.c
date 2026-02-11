gui_editor_is_marked (GUIEditor * self, gint ln)
{
  GtkTextIter line_start, line_end;
  GSList *list_iter;


  gtk_text_buffer_get_iter_at_line (GTK_TEXT_BUFFER (self->buffer), &line_start, ln);
  line_end = line_start;
  gtk_text_iter_forward_to_line_end (&line_end);


  list_iter = gtk_source_buffer_get_source_marks_at_iter (self->buffer, &line_start, NULL);


  while (list_iter != NULL)
	{
	  GtkSourceMark *tmp = list_iter->data;
	  const gchar *tmp_type = gtk_source_mark_get_category (tmp);
	  if (tmp_type && !strcmp (tmp_type, MARKER_BREAKPOINT))
		{
		  return TRUE;
		}
	  list_iter = g_slist_next (list_iter);
	}

  return FALSE;
}
