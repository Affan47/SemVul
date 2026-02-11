test_search_async (Test *test,
                   gconstpointer used)
{
	GAsyncResult *result = NULL;
	GHashTable *attributes;
	GError *error = NULL;
	GList *items;

	attributes = g_hash_table_new (g_str_hash, g_str_equal);
	g_hash_table_insert (attributes, "number", "1");

	secret_service_search (test->service, &MOCK_SCHEMA, attributes,
	                       SECRET_SEARCH_NONE, NULL,
	                       on_complete_get_result, &result);
	g_hash_table_unref (attributes);
	g_assert (result == NULL);

	egg_test_wait ();

	g_assert (G_IS_ASYNC_RESULT (result));
	items = secret_service_search_finish (test->service, result, &error);
	g_assert_no_error (error);
	g_object_unref (result);

	g_assert (items != NULL);
	g_assert_cmpstr (g_dbus_proxy_get_object_path (items->data), ==, "/org/freedesktop/secrets/collection/english/1");

	g_assert (items->next == NULL);
	g_list_free_full (items, g_object_unref);
}
