on_store_keyring (GObject *source,
                  GAsyncResult *result,
                  gpointer user_data)
{
	GSimpleAsyncResult *async = G_SIMPLE_ASYNC_RESULT (user_data);
	StoreClosure *store = g_simple_async_result_get_op_res_gpointer (async);
	SecretService *service = SECRET_SERVICE (source);
	GError *error = NULL;
	gchar *path;

	path = secret_service_create_collection_dbus_path_finish (service, result, &error);
	if (error == NULL) {
		store->created_collection = TRUE;
		secret_service_create_item_dbus_path (service, store->collection_path,
		                                      store->properties, store->value,
		                                      SECRET_ITEM_CREATE_REPLACE, store->cancellable,
		                                      on_store_create, g_object_ref (async));
	} else {
		g_simple_async_result_take_error (async, error);
		g_simple_async_result_complete (async);
	}

	g_object_unref (async);
	g_free (path);
}
