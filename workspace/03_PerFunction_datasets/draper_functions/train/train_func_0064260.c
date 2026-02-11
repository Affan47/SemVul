show_message(GtkMessageType type, const char* text, const char* details)
{
	GtkWidget *dialog;

	g_assert(text);

	dialog = gtk_message_dialog_new (NULL, DIALOG_FLAGS, type, GTK_BUTTONS_CLOSE,
					 "%s", text);
	if (details) {
		gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "%s", details);
	}
	gtk_dialog_run(GTK_DIALOG (dialog));
	gtk_widget_destroy(dialog);
}
