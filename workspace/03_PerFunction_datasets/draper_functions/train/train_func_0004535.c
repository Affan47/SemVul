brasero_jacket_view_scrolled_cb (GtkAdjustment *adj,
				 GtkTextView *view)
{
	gint trailing;
	GtkTextIter end;
	GtkTextIter start;
	GdkRectangle rect;
	GtkTextBuffer *buffer;

	if (gtk_adjustment_get_value (adj) == 0.0)
		return;

	g_signal_stop_emission_by_name (adj, "value-changed");

	buffer = gtk_text_view_get_buffer (view);

	gtk_text_buffer_get_end_iter (buffer, &end);

	gtk_text_view_get_visible_rect (view, &rect);
	gtk_text_view_get_iter_at_position (view,
					    &start,
					    &trailing,
					    rect.x + rect.width,
					    rect.y + rect.height - gtk_adjustment_get_value (adj));
	gtk_text_buffer_delete (buffer, &start, &end);

	gtk_adjustment_set_value (adj, 0.0);
}
