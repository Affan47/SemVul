tracker_file_unlock (GFile *file)
{
	gint retval, fd;

	g_return_val_if_fail (G_IS_FILE (file), TRUE);

	if (!file_locks) {
		return TRUE;
	}

	fd = GPOINTER_TO_INT (g_hash_table_lookup (file_locks, file));

	if (fd == 0) {

		return TRUE;
	}

	retval = flock (fd, LOCK_UN);

	if (retval < 0) {

		gchar *uri;

		uri = g_file_get_uri (file);
		g_warning ("Could not unlock file '%s'", uri);
		g_free (uri);

		return FALSE;

	}

	g_hash_table_remove (file_locks, file);
	close (fd);

	return TRUE;
}
