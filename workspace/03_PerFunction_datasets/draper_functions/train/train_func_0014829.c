on_help_cb (GtkAction *action, BraseroApp *app)
{
	GError *error = NULL;
	BraseroAppPrivate *priv;

	priv = BRASERO_APP_PRIVATE (app);

	gtk_show_uri (NULL, "help:brasero", gtk_get_current_event_time (), &error);
   	if (error) {
		GtkWidget *d;

		d = gtk_message_dialog_new (GTK_WINDOW (priv->mainwin),
					    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
					    GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
					    "%s", error->message);
		gtk_dialog_run (GTK_DIALOG(d));
		gtk_widget_destroy (d);
		g_error_free (error);
		error = NULL;
	}
}
