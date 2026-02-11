test_delete_for_path_sync (Test *test,
                           gconstpointer used)

{
	const gchar *path_item_one = "/org/freedesktop/secrets/collection/todelete/item";
	GError *error = NULL;
	gboolean ret;

	ret = secret_service_delete_item_dbus_path_sync (test->service, path_item_one, NULL, &error);
	g_assert_no_error (error);
	g_assert (ret == TRUE);
}
