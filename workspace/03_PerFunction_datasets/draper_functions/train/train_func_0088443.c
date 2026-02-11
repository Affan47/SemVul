start_interactive_search_real (GeditViewFrame *frame,
			       SearchMode      request_search_mode)
{
	GtkTextBuffer *buffer;
	GtkTextIter iter;

	if (gtk_revealer_get_reveal_child (frame->priv->revealer))
	{
		if (frame->priv->search_mode != request_search_mode)
		{
			hide_search_widget (frame, TRUE);
		}
		else
		{
			gtk_editable_select_region (GTK_EDITABLE (frame->priv->search_entry),
			                            0, -1);
			return;
		}
	}

	frame->priv->search_mode = request_search_mode;

	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (frame->priv->view));

	if (frame->priv->search_mode == SEARCH)
	{
		gtk_text_buffer_get_selection_bounds (buffer, &iter, NULL);
	}
	else
	{
		GtkTextMark *mark = gtk_text_buffer_get_insert (buffer);
		gtk_text_buffer_get_iter_at_mark (buffer, &iter, mark);
	}

	if (frame->priv->start_mark != NULL)
	{
		gtk_text_buffer_delete_mark (buffer, frame->priv->start_mark);
	}

	frame->priv->start_mark = gtk_text_buffer_create_mark (buffer, NULL, &iter, FALSE);

	gtk_revealer_set_reveal_child (frame->priv->revealer, TRUE);


	g_signal_handler_block (frame->priv->search_entry,
	                        frame->priv->search_entry_changed_id);

	gtk_entry_set_text (GTK_ENTRY (frame->priv->search_entry), "");

	g_signal_handler_unblock (frame->priv->search_entry,
	                          frame->priv->search_entry_changed_id);

	gtk_widget_grab_focus (GTK_WIDGET (frame->priv->search_entry));

	customize_for_search_mode (frame);
	init_search_entry (frame);


	frame->priv->view_scroll_event_id =
		g_signal_connect (frame->priv->view, "scroll-event",
			          G_CALLBACK (search_widget_scroll_event),
			          frame);

	renew_flush_timeout (frame);

	install_update_entry_tag_idle (frame);
}
