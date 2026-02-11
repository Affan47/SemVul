object_path_for_collection (GckObject *collection)
{
	GError *error = NULL;
	gpointer identifier;
	gsize n_identifier;
	gchar *path = NULL;

	identifier = gck_object_get_data (collection, CKA_ID, NULL, &n_identifier, &error);
	if (identifier == NULL) {
		g_warning ("couldn't get collection identifier: %s", egg_error_message (error));
		g_clear_error (&error);
		path = NULL;

	} else {
		path = gkd_secret_util_build_path (SECRET_COLLECTION_PREFIX, identifier, n_identifier);
		g_free (identifier);
	}

	return path;
}
