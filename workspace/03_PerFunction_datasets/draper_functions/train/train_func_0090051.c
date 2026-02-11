test_new_async_noexist (Test *test,
                        gconstpointer unused)
{
	const gchar *item_path = "/org/freedesktop/secrets/collection/english/0000";
	GAsyncResult *result = NULL;
	GError *error = NULL;
	SecretItem *item;

	secret_item_new_for_dbus_path (test->service, item_path, SECRET_ITEM_NONE,
	                               NULL, on_async_result, &result);
	g_assert (result == NULL);

	egg_test_wait ();

	item = secret_item_new_for_dbus_path_finish (result, &error);
	g_assert_error (error, G_DBUS_ERROR, G_DBUS_ERROR_UNKNOWN_METHOD);
	g_assert (item == NULL);
	g_object_unref (result);
}
