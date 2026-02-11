policy_view_on_line_event(GtkTextTag * tag
					  __attribute__ ((unused)), GObject * event_object
					  __attribute__ ((unused)), GdkEvent * event, const GtkTextIter * iter, gpointer user_data)
{
	policy_view_t *pv = (policy_view_t *) user_data;
	GtkTextIter start, end;
	int line;
	GtkTextView *view;
	if (event->type != GDK_BUTTON_PRESS) {
		return FALSE;
	}
	start = *iter;
	while (!gtk_text_iter_starts_word(&start))
		gtk_text_iter_backward_char(&start);
	end = start;
	while (!gtk_text_iter_ends_word(&end))
		gtk_text_iter_forward_char(&end);

	line = atoi(gtk_text_iter_get_slice(&start, &end)) - 1;
	view = GTK_TEXT_VIEW(glade_xml_get_widget(pv->xml, "PolicyWindowPolicyText"));
	assert(view != NULL);
	gtk_notebook_set_current_page(pv->notebook, 1);
	gtk_text_buffer_get_start_iter(pv->policy_text, &start);
	gtk_text_iter_set_line(&start, line);
	gtk_text_view_scroll_to_iter(view, &start, 0.0001, TRUE, 0.0, 0.5);
	gtk_text_buffer_place_cursor(pv->policy_text, &start);
	gtk_text_view_set_cursor_visible(view, TRUE);
	return TRUE;
}
