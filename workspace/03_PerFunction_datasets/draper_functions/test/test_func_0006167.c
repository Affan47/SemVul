fsel_response_cb (GtkFileChooser *dialog,
		  gint response_id,
		  gboolean *result)
{
	if (response_id == GTK_RESPONSE_OK) {
		char *uri = gtk_file_chooser_get_uri (dialog);

		if (uri) {
			g_free (uri);
			*result = TRUE;
		}
	}

	gtk_main_quit ();
}
