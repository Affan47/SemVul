secret_collection_create (SecretService *service,
                          const gchar *label,
                          const gchar *alias,
                          SecretCollectionCreateFlags flags,
                          GCancellable *cancellable,
                          GAsyncReadyCallback callback,
                          gpointer user_data)
{
	GSimpleAsyncResult *res;
	CreateClosure *closure;

	g_return_if_fail (service == NULL || SECRET_IS_SERVICE (service));
	g_return_if_fail (label != NULL);
	g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));

	res = g_simple_async_result_new (NULL, callback, user_data,
	                                 secret_collection_create);
	closure = g_slice_new0 (CreateClosure);
	closure->cancellable = cancellable ? g_object_ref (cancellable) : NULL;
	closure->properties = _secret_collection_properties_new (label);
	closure->alias = g_strdup (alias);
	closure->flags = flags;
	g_simple_async_result_set_op_res_gpointer (res, closure, create_closure_free);

	if (service == NULL) {
		secret_service_get (SECRET_SERVICE_NONE, cancellable,
		                    on_create_service, g_object_ref (res));

	} else {
		secret_service_create_collection_dbus_path (service, closure->properties,
		                                            closure->alias, closure->flags,
		                                            closure->cancellable,
		                                            on_create_path, g_object_ref (res));
	}

	g_object_unref (res);
}
