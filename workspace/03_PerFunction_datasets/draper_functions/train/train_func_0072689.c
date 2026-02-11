ch_ccmx_add_local_files (ChCcmxPrivate *priv)
{
	const gchar *tmp;
	gboolean ret;
	gchar *location;
	gchar *location_tmp;
	GDir *dir;
	GError *error = NULL;


	location = g_build_filename (g_get_user_data_dir (),
				     "colorhug-ccmx",
				     NULL);
	dir = g_dir_open (location, 0, &error);
	if (dir == NULL) {
		g_warning ("Failed to get directory: %s", error->message);
		g_error_free (error);
		goto out;
	}
	while (TRUE) {
		tmp = g_dir_read_name (dir);
		if (tmp == NULL)
			break;
		location_tmp = g_build_filename (location, tmp, NULL);
		ret = ch_ccmx_add_local_file (priv, location_tmp, &error);
		if (!ret) {
			g_warning ("Failed to add file %s: %s",
				   location_tmp, error->message);
			g_error_free (error);
			goto out;
		}
		g_free (location_tmp);
	}
out:
	if (dir != NULL)
		g_dir_close (dir);
	g_free (location);
}
