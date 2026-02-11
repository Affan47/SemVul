error_dialog (const char *title,
	      const char *reason,
	      GtkWindow *parent)
{
	GtkWidget *error_dialog;

	if (reason == NULL)
		reason = _("No reason");

	error_dialog =
		gtk_message_dialog_new (parent,
					GTK_DIALOG_MODAL,
					GTK_MESSAGE_ERROR,
					GTK_BUTTONS_OK,
					"%s", title);
	gtk_message_dialog_format_secondary_text
		(GTK_MESSAGE_DIALOG (error_dialog), "%s", reason);

	gtk_window_set_title (GTK_WINDOW (error_dialog), "");
	gtk_container_set_border_width (GTK_CONTAINER (error_dialog), 5);
	gtk_dialog_set_default_response (GTK_DIALOG (error_dialog),
					 GTK_RESPONSE_OK);
	gtk_window_set_modal (GTK_WINDOW (error_dialog), TRUE);

	return error_dialog;
}
