migrate_keyring_entry (const gchar *uid,
                       const gchar *user,
                       const gchar *server,
                       const gchar *protocol)
{
	GHashTable *attributes;
	GList *found_list = NULL;
	gchar *display_name;


	if (!user || !server || !protocol) {
	      return;
	}


	display_name = g_strdup_printf (KEYRING_ITEM_DISPLAY_FORMAT, uid);

	attributes = secret_attributes_build (
		&e_passwords_schema,
		"application", "Evolution",
		"user", user,
		"server", server,
		"protocol", protocol,
		NULL);

	found_list = secret_service_search_sync (
		NULL, &e_passwords_schema, attributes,
		SECRET_SEARCH_ALL |
		SECRET_SEARCH_UNLOCK |
		SECRET_SEARCH_LOAD_SECRETS,
		NULL, NULL);


	if (found_list != NULL) {
		SecretItem *item = found_list->data;
		SecretValue *secret = secret_item_get_secret (item);


		g_return_if_fail (secret != NULL);

		secret_password_store_sync (
			&schema, SECRET_COLLECTION_DEFAULT, display_name,
			secret_value_get (secret, NULL), NULL, NULL,
			KEYRING_ITEM_ATTRIBUTE_NAME, uid, NULL);

		secret_value_unref (secret);
	}

	g_list_free_full (found_list, g_object_unref);
	g_hash_table_unref (attributes);

	g_free (display_name);
}
