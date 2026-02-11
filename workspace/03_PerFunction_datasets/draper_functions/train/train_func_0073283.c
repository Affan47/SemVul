test_search_secrets_sync (Test *test,
                          gconstpointer used)
{
	const gchar *collection_path = "/org/freedesktop/secrets/collection/english";
	SecretCollection *collection;
	GHashTable *attributes;
	GError *error = NULL;
	SecretValue *value;
	GList *items;

	collection = secret_collection_new_for_dbus_path_sync (test->service, collection_path,
	                                                       SECRET_COLLECTION_NONE, NULL, &error);
	g_assert_no_error (error);

	attributes = g_hash_table_new (g_str_hash, g_str_equal);
	g_hash_table_insert (attributes, "number", "1");

	items = secret_collection_search_sync (collection, &MOCK_SCHEMA, attributes,
	                                       SECRET_SEARCH_LOAD_SECRETS,
	                                       NULL, &error);
	g_assert_no_error (error);
	g_hash_table_unref (attributes);

	g_assert (items != NULL);
	g_assert_cmpstr (g_dbus_proxy_get_object_path (items->data), ==, "/org/freedesktop/secrets/collection/english/1");
	g_assert (secret_item_get_locked (items->data) == FALSE);
	value = secret_item_get_secret (items->data);
	g_assert (value != NULL);
	secret_value_unref (value);

	g_assert (items->next == NULL);
	g_list_free_full (items, g_object_unref);

	g_object_unref (collection);
}
