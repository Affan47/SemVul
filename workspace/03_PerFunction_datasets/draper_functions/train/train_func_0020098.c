msg_box (	gchar		*message,
		GtkMessageType	msg_type       )


{
	GtkWidget *msg_dialog;

	msg_dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, msg_type, GTK_BUTTONS_OK, message);


	gtk_grab_add (GTK_WIDGET(msg_dialog));
	gtk_dialog_run (GTK_DIALOG (msg_dialog));
	gtk_widget_destroy (msg_dialog);

	while (g_main_context_iteration(NULL, FALSE))
		;
}
