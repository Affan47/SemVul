gjiten_print_error(const char *fmt, ... ) {
	GtkWidget *dialog;
	gint ret = -1;
	va_list args;
	gchar *pstr;

	va_start(args, fmt);
	pstr = g_strdup_vprintf(fmt, args);
	va_end(args);

	if (pstr != NULL) {
	  dialog = gtk_message_dialog_new(NULL, 0, GTK_MESSAGE_ERROR,  GTK_BUTTONS_OK, "%s", pstr );

		g_signal_connect_swapped(GTK_OBJECT(dialog), "response",
														 G_CALLBACK(gtk_widget_destroy),
														 GTK_OBJECT(dialog));

		gtk_widget_show_all(dialog);
	  g_free(pstr);
	}
	return ret;
}
