perform_recreate (gboolean *first_time, GError **error)
{
	GError *internal_error = NULL;
	guint i;

	if (first_time) {
		*first_time = TRUE;
	}

	for (i = 1; i < G_N_ELEMENTS (dbs); i++) {
		if (dbs[i].iface) {
			g_object_unref (dbs[i].iface);
			dbs[i].iface = NULL;
		}
	}

	if (!tracker_file_system_has_enough_space (data_dir, TRACKER_DB_MIN_REQUIRED_SPACE, TRUE)) {
		g_set_error (error,
		             TRACKER_DB_INTERFACE_ERROR,
		             TRACKER_DB_OPEN_ERROR,
		             "Filesystem has not enough space");
		return;
	}

	db_recreate_all (&internal_error);

	if (internal_error) {
		g_propagate_error (error, internal_error);
	}
}
