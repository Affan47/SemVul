e_notice (gpointer parent,
          GtkMessageType type,
          const gchar *format,
          ...)
{
	GtkWidget *dialog;
	va_list args;
	gchar *str;

	va_start (args, format);
	str = g_strdup_vprintf (format, args);

	dialog = gtk_message_dialog_new (
		NULL, GTK_DIALOG_DESTROY_WITH_PARENT,
		type, GTK_BUTTONS_OK, "%s", str);
	va_end (args);
	g_free (str);

	if (parent && !gtk_widget_is_toplevel (parent))
		parent = gtk_widget_get_toplevel (parent);
	if (parent)
		gtk_window_set_transient_for (GTK_WINDOW (dialog), parent);

	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}
