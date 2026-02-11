db_interface_create (TrackerDB db,
                     GError **error)
{
	TrackerDBInterface *iface;
	GError *internal_error = NULL;

	switch (db) {
	case TRACKER_DB_UNKNOWN:
		return NULL;

	case TRACKER_DB_METADATA:
		iface = db_interface_get_metadata (&internal_error);
		if (internal_error) {
			g_propagate_error (error, internal_error);
			return NULL;
		}
		return iface;

	default:
		g_critical ("This TrackerDB type:%d->'%s' has no interface set up yet!!",
		            db,
		            db_type_to_string (db));
		return NULL;
	}
}
