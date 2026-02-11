display_dialog_character_set_conversion_error (GtkWidget * window,
                                               gchar * string,
                                               GError * error)
{
	GtkWidget * dialog;

	dialog = gtk_message_dialog_new (GTK_WINDOW (window),
 	                                 GTK_DIALOG_DESTROY_WITH_PARENT,
	                                 GTK_MESSAGE_ERROR,
	                                 GTK_BUTTONS_OK,
	                                 _("Character set conversion failed for \"%s\""),
					 string);

	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
	                                          (error == NULL) ? " " : error->message, NULL);

	g_signal_connect (G_OBJECT (dialog),
	                  "response",
	                   G_CALLBACK (gtk_widget_destroy), NULL);

	gtk_widget_show (dialog);
}
