drive_poll_for_media_cb (GObject      *source_object,
			 GAsyncResult *res,
			 gpointer      user_data)
{
	GdkScreen *screen;
	GError    *error;
	char      *primary;
	char      *name;

	error = NULL;
	if (!g_drive_poll_for_media_finish (G_DRIVE (source_object),
					    res, &error)) {
		if (error->code != G_IO_ERROR_FAILED_HANDLED) {
			screen = GDK_SCREEN (user_data);

			name = g_drive_get_name (G_DRIVE (source_object));
			primary = g_strdup_printf (_("Unable to scan %s for media changes"),
						   name);
			g_free (name);
			panel_error_dialog (NULL, screen,
					    "cannot_scan_drive", TRUE,
					    primary, error->message);
			g_free (primary);
		}
		g_error_free (error);
	}


}
