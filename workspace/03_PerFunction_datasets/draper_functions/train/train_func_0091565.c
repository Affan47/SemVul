forward_search_finished (GtkSourceSearchContext *search_context,
			 GAsyncResult           *result,
			 GeditView              *view)
{
	gboolean found;
	GtkSourceBuffer *buffer;
	GtkTextIter match_start;
	GtkTextIter match_end;

	found = gtk_source_search_context_forward_finish (search_context,
							  result,
							  &match_start,
							  &match_end,
							  NULL);

	buffer = gtk_source_search_context_get_buffer (search_context);

	if (found)
	{
		gtk_text_buffer_select_range (GTK_TEXT_BUFFER (buffer),
					      &match_start,
					      &match_end);

		gedit_view_scroll_to_cursor (view);
	}
	else
	{
		GtkTextIter end_selection;

		gtk_text_buffer_get_selection_bounds (GTK_TEXT_BUFFER (buffer),
						      NULL,
						      &end_selection);

		gtk_text_buffer_select_range (GTK_TEXT_BUFFER (buffer),
					      &end_selection,
					      &end_selection);
	}

	return found;
}
