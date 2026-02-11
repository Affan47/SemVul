find_saved_items (GckSession *session, GckAttributes *attrs)
{
	GckBuilder builder = GCK_BUILDER_INIT;
	GError *error = NULL;
	const GckAttribute *attr;
	GckObject *search;
	GList *results;
	gpointer data;
	gsize n_data;

	gck_builder_add_ulong (&builder, CKA_CLASS, CKO_G_SEARCH);
	gck_builder_add_boolean (&builder, CKA_TOKEN, FALSE);

	attr = gck_attributes_find (attrs, CKA_G_COLLECTION);
	if (attr != NULL)
		gck_builder_add_attribute (&builder, attr);

	attr = gck_attributes_find (attrs, CKA_G_FIELDS);
	g_return_val_if_fail (attr != NULL, NULL);
	gck_builder_add_attribute (&builder, attr);

	search = gck_session_create_object (session, gck_builder_end (&builder), NULL, &error);
	if (search == NULL) {
		g_warning ("couldn't perform search for gpg agent stored passphrases: %s",
		           egg_error_message (error));
		g_clear_error (&error);
		return NULL;
	}

	data = gck_object_get_data (search, CKA_G_MATCHED, NULL, &n_data, &error);
	gck_object_destroy (search, NULL, NULL);
	g_object_unref (search);

	if (data == NULL) {
		g_warning ("couldn't retrieve list of gpg agent stored passphrases: %s",
		           egg_error_message (error));
		g_clear_error (&error);
		return NULL;
	}

	results = gck_objects_from_handle_array (session, data, n_data / sizeof (CK_ULONG));

	g_free (data);
	return results;
}
