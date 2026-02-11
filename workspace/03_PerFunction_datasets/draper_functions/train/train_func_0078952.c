toplevel_on_help_activate(gpointer user_data, GtkMenuItem * widget __attribute__ ((unused)))
{
	toplevel_t *top = g_object_get_data(G_OBJECT(user_data), "toplevel");
	GtkWidget *window;
	GtkWidget *scroll;
	GtkWidget *text_view;
	GtkTextBuffer *buffer;
	char *help_text = NULL;
	size_t len;
	int rt;
	char *dir;

	window = gtk_dialog_new_with_buttons("seaudit Help",
					     GTK_WINDOW(top->w),
					     GTK_DIALOG_DESTROY_WITH_PARENT, GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE, NULL);
	gtk_dialog_set_default_response(GTK_DIALOG(window), GTK_RESPONSE_CLOSE);
	g_signal_connect_swapped(window, "response", G_CALLBACK(gtk_widget_destroy), window);
	scroll = gtk_scrolled_window_new(NULL, NULL);
	text_view = gtk_text_view_new();
	gtk_window_set_default_size(GTK_WINDOW(window), 520, 300);
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(window)->vbox), scroll);
	gtk_container_add(GTK_CONTAINER(scroll), text_view);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_NONE);
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
	dir = apol_file_find_path("seaudit_help.txt");
	if (!dir) {
		toplevel_ERR(top, "Cannot find help file.");
		return;
	}
	rt = apol_file_read_to_buffer(dir, &help_text, &len);
	free(dir);
	if (rt != 0) {
		free(help_text);
		return;
	}
	gtk_text_buffer_set_text(buffer, help_text, len);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ON_PARENT);
	gtk_widget_show(text_view);
	gtk_widget_show(scroll);
	gtk_widget_show(window);
}
