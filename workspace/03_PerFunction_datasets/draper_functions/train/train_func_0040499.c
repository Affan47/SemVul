cursor_advance (gint n)
{
	gint i;
	gboolean cursor_out_screen;
	GtkWidget *wg;
	GtkTextBuffer *buf;
	GtkTextIter new_start;
	GtkTextIter old_start;
	GtkTextIter end;
	GtkTextMark *mark;

	wg = get_wg ("text_tutor");
	buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (wg));


	gtk_text_buffer_get_iter_at_mark (buf, &new_start, gtk_text_buffer_get_insert (buf));
	old_start = new_start;


	if (n > 0)
		for (i = 0; i < n && gtk_text_iter_forward_cursor_position (&new_start); i++);
	else
		for (i = 0; i > n && gtk_text_iter_backward_cursor_position (&new_start); i--);


	end = new_start;
	gtk_text_iter_forward_char (&end);
	gtk_text_buffer_apply_tag_by_name (buf, "cursor_blink", &new_start, &end);

	end = old_start;
	gtk_text_iter_forward_char (&end);
	gtk_text_buffer_remove_tag_by_name (buf, "cursor_blink", &old_start, &end);


	gtk_text_buffer_place_cursor (buf, &new_start);


	if (i == n)
	{
		end = new_start;
		gtk_text_iter_forward_line (&end);
		mark = gtk_text_buffer_create_mark (buf, "aux", &end, FALSE);
		cursor_out_screen = gtk_text_view_move_mark_onscreen (GTK_TEXT_VIEW (wg), mark);
		if (cursor_out_screen)
		{
			gtk_text_view_scroll_to_mark (GTK_TEXT_VIEW (wg),
				       	gtk_text_buffer_get_insert (buf), 0.0, TRUE, 0.5, 0.12);
		}
	}
	return (i);
}
