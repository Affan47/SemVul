source_config_dialog_commit_cb (GObject *object,
                                GAsyncResult *result,
                                gpointer user_data)
{
	ESourceConfig *config;
	ESourceConfigDialog *dialog;
	GdkWindow *gdk_window;
	GError *error = NULL;

	config = E_SOURCE_CONFIG (object);
	dialog = E_SOURCE_CONFIG_DIALOG (user_data);


	gdk_window = gtk_widget_get_window (GTK_WIDGET (dialog));
	gdk_window_set_cursor (gdk_window, NULL);


	gtk_widget_set_sensitive (GTK_WIDGET (dialog), TRUE);

	e_source_config_commit_finish (config, result, &error);


	if (g_error_matches (error, G_IO_ERROR, G_IO_ERROR_CANCELLED)) {
		g_object_unref (dialog);
		g_error_free (error);

	} else if (error != NULL) {
		e_alert_submit (
			E_ALERT_SINK (dialog),
			"system:simple-error",
			error->message, NULL);
		g_object_unref (dialog);
		g_error_free (error);

	} else {
		gtk_widget_destroy (GTK_WIDGET (dialog));
	}
}
