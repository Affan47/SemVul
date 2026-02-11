google_chooser_dialog_populated_cb (EGoogleChooser *chooser,
                                    GAsyncResult *result,
                                    EGoogleChooserDialog *dialog)
{
	GdkWindow *window;
	GError *error = NULL;

	e_google_chooser_populate_finish (chooser, result, &error);


	if (g_error_matches (error, G_IO_ERROR, G_IO_ERROR_CANCELLED))
		goto exit;


	window = gtk_widget_get_window (GTK_WIDGET (dialog));
	gdk_window_set_cursor (window, NULL);

	if (error != NULL) {
		GtkLabel *label;

		label = GTK_LABEL (dialog->priv->info_bar_label);
		gtk_label_set_text (label, error->message);
		gtk_widget_show (dialog->priv->info_bar);

		g_error_free (error);
		goto exit;
	}

exit:
	g_object_unref (dialog);
}
