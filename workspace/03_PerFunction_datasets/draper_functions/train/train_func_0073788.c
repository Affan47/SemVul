eel_show_error_dialog_with_details (const char *primary_text,
				    const char *secondary_text,
				    const char *detailed_error_message,
				    GtkWindow *parent)
{
	GtkDialog *dialog;

	g_return_val_if_fail (primary_text != NULL, NULL);
	g_return_val_if_fail (parent == NULL || GTK_IS_WINDOW (parent), NULL);

	if (detailed_error_message == NULL
	    || strcmp (primary_text, detailed_error_message) == 0) {
		return eel_show_error_dialog (primary_text, secondary_text, parent);
	}

	dialog = show_message_dialog (primary_text,
				      secondary_text,
				      GTK_MESSAGE_ERROR,
				      GTK_BUTTONS_OK, detailed_error_message,
				      parent);
	return dialog;
}
