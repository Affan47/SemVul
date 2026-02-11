create_image_widget (NautilusPropertiesWindow *window,
		     gboolean is_customizable)
{
 	GtkWidget *button;
	GtkWidget *image;

	image = gtk_image_new ();
	window->details->icon_image = image;

	update_properties_window_icon (window);
	gtk_widget_show (image);

	button = NULL;
	if (is_customizable) {
		button = gtk_button_new ();
		gtk_container_add (GTK_CONTAINER (button), image);


		gtk_drag_dest_set (GTK_WIDGET (image),
				   GTK_DEST_DEFAULT_MOTION | GTK_DEST_DEFAULT_HIGHLIGHT | GTK_DEST_DEFAULT_DROP,
				   target_table, G_N_ELEMENTS (target_table),
				   GDK_ACTION_COPY | GDK_ACTION_MOVE);

		g_signal_connect (image, "drag-data-received",
				  G_CALLBACK (nautilus_properties_window_drag_data_received), NULL);
		g_signal_connect (button, "clicked",
				  G_CALLBACK (select_image_button_callback), window);
	}

	window->details->icon_button = button;

	return button != NULL ? button : image;
}
