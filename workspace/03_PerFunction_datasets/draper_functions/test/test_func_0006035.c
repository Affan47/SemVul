db_interface_get_metadata (GError **error)
{
	TrackerDBInterface *iface;
	gboolean create;
	GError *internal_error = NULL;

	iface = db_interface_get (TRACKER_DB_METADATA, &create, &internal_error);

	if (internal_error) {
		g_propagate_error (error, internal_error);
		return NULL;
	}

	return iface;
}
