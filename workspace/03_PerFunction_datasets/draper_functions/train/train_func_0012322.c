new_view_cb (GtkAction *action,
	     gpointer   user_data)
{
	GtkSourceBuffer *buffer;
	GtkSourceView *view;
	GtkWidget *window;

	g_return_if_fail (GTK_SOURCE_IS_VIEW (user_data));

	view = GTK_SOURCE_VIEW (user_data);
	buffer = GTK_SOURCE_BUFFER (gtk_text_view_get_buffer (GTK_TEXT_VIEW (view)));

	window = create_view_window (buffer, view);
	gtk_window_set_default_size (GTK_WINDOW (window), 400, 400);
	gtk_widget_show (window);
}
