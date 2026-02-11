secret_service_set_alias (SecretService *service,
                          const gchar *alias,
                          SecretCollection *collection,
                          GCancellable *cancellable,
                          GAsyncReadyCallback callback,
                          gpointer user_data)
{
	GSimpleAsyncResult *async;
	SetClosure *set;
	const gchar *path;

	g_return_if_fail (service == NULL || SECRET_IS_SERVICE (service));
	g_return_if_fail (alias != NULL);
	g_return_if_fail (collection == NULL || SECRET_IS_COLLECTION (collection));
	g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));

	async = g_simple_async_result_new (G_OBJECT (service), callback, user_data,
	                                   secret_service_set_alias);
	set = g_slice_new0 (SetClosure);
	set->cancellable = cancellable ? g_object_ref (cancellable) : NULL;
	set->alias = g_strdup (alias);

	if (collection) {
		path = g_dbus_proxy_get_object_path (G_DBUS_PROXY (collection));
		g_return_if_fail (path != NULL);
	} else {
		path = NULL;
	}

	set->collection_path = g_strdup (path);
	g_simple_async_result_set_op_res_gpointer (async, set, set_closure_free);

	if (service == NULL) {
		secret_service_get (SECRET_SERVICE_NONE, cancellable,
		                    on_set_alias_service, g_object_ref (async));
	} else {
		secret_service_set_alias_to_dbus_path (service, set->alias,
		                                       set->collection_path,
		                                       set->cancellable,
		                                       on_set_alias_done,
		                                       g_object_ref (async));
	}

	g_object_unref (async);
}
