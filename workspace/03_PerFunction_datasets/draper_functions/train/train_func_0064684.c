dma_data_view_goto_activate (GtkWidget   *menu_item,
			     DmaDataView *view)
{
	GtkWidget *toplevel;
	GtkWidget *frame;
	GtkWidget *vbox;
	GtkWindowGroup *toplevel_group;
	GtkWindowGroup *goto_window_group;

	toplevel = gtk_widget_get_toplevel (GTK_WIDGET (view));
	toplevel_group = gtk_window_get_group (GTK_WINDOW (toplevel));
	goto_window_group = gtk_window_get_group (GTK_WINDOW (view->goto_window));

	if (view->goto_window != NULL)
	{
		if (toplevel_group)
			gtk_window_group_add_window (toplevel_group,
						     GTK_WINDOW (view->goto_window));
		else if (goto_window_group)
			gtk_window_group_remove_window (goto_window_group,
							GTK_WINDOW (view->goto_window));

	}
	else
	{
		view->goto_window = gtk_window_new (GTK_WINDOW_POPUP);

		if (toplevel_group)
			gtk_window_group_add_window (toplevel_group,
						     GTK_WINDOW (view->goto_window));

		gtk_window_set_modal (GTK_WINDOW (view->goto_window), TRUE);
		g_signal_connect (view->goto_window, "delete_event",
						  G_CALLBACK (dma_data_view_goto_delete_event),
						  view);
		g_signal_connect (view->goto_window, "key_press_event",
						  G_CALLBACK (dma_data_view_goto_key_press_event),
						  view);

		frame = gtk_frame_new (NULL);
		gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_ETCHED_IN);
		gtk_widget_show (frame);
		gtk_container_add (GTK_CONTAINER (view->goto_window), frame);

		vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
		gtk_widget_show (vbox);
		gtk_container_add (GTK_CONTAINER (frame), vbox);
		gtk_container_set_border_width (GTK_CONTAINER (vbox), 3);


		view->goto_entry = gtk_entry_new ();
		gtk_entry_set_icon_from_stock (GTK_ENTRY (view->goto_entry),
									   GTK_ENTRY_ICON_PRIMARY,
									   GTK_STOCK_JUMP_TO);
		gtk_widget_show (view->goto_entry);
		gtk_container_add (GTK_CONTAINER (vbox),
						   view->goto_entry);

		gtk_widget_realize (view->goto_entry);
	}

	dma_data_view_goto_position_func (view);
	gtk_entry_set_text (GTK_ENTRY (view->goto_entry), "0x");
	gtk_widget_show (view->goto_window);

	gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view->address), FALSE);
    gtk_widget_grab_focus (view->goto_entry);
    send_focus_change (view->goto_entry, TRUE);
	gtk_editable_set_position (GTK_EDITABLE (view->goto_entry), -1);
}
