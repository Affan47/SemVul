test_open_more_sync (Test *test,
                    gconstpointer data)
{
	SecretService *service;
	GError *error = NULL;
	const gchar *path;
	GList *collections;

	service = secret_service_open_sync (SECRET_TYPE_SERVICE, NULL, SECRET_SERVICE_NONE,
	                                    NULL, &error);
	g_assert_no_error (error);
	g_assert (SECRET_IS_SERVICE (service));
	g_object_add_weak_pointer (G_OBJECT (service), (gpointer *)&service);

	g_assert_cmpuint (secret_service_get_flags (service), ==, SECRET_SERVICE_NONE);
	g_assert (secret_service_get_collections (service) == NULL);
	g_assert (secret_service_get_session_dbus_path (service) == NULL);

	g_object_unref (service);
	g_assert (service == NULL);

	service = secret_service_open_sync (SECRET_TYPE_SERVICE, NULL,
	                                    SECRET_SERVICE_LOAD_COLLECTIONS, NULL, &error);
	g_assert_no_error (error);
	g_assert (SECRET_IS_SERVICE (service));
	g_object_add_weak_pointer (G_OBJECT (service), (gpointer *)&service);

	g_assert_cmpuint (secret_service_get_flags (service), ==, SECRET_SERVICE_LOAD_COLLECTIONS);
	collections = secret_service_get_collections (service);
	g_assert (collections != NULL);
	g_list_free_full (collections, g_object_unref);
	g_assert (secret_service_get_session_dbus_path (service) == NULL);

	g_object_unref (service);
	g_assert (service == NULL);

	service = secret_service_open_sync (SECRET_TYPE_SERVICE, NULL,
	                                    SECRET_SERVICE_OPEN_SESSION, NULL, &error);
	g_assert_no_error (error);
	g_assert (SECRET_IS_SERVICE (service));
	g_object_add_weak_pointer (G_OBJECT (service), (gpointer *)&service);

	g_assert_cmpuint (secret_service_get_flags (service), ==, SECRET_SERVICE_OPEN_SESSION);
	g_assert (secret_service_get_collections (service) == NULL);
	path = secret_service_get_session_dbus_path (service);
	g_assert (path != NULL);

	g_object_unref (service);
	g_assert (service == NULL);
}
