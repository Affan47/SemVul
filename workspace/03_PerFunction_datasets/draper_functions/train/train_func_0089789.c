service_disconnect_thread (GSimpleAsyncResult *simple,
                           GObject *object,
                           GCancellable *cancellable)
{
	CamelService *service;
	CamelServiceClass *class;
	gboolean clean;
	GError *error = NULL;


	service = CAMEL_SERVICE (object);
	clean = g_simple_async_result_get_op_res_gboolean (simple);

	class = CAMEL_SERVICE_GET_CLASS (service);
	g_return_if_fail (class->disconnect_sync != NULL);

	class->disconnect_sync (service, clean, cancellable, &error);

	if (error != NULL)
		g_simple_async_result_take_error (simple, error);
}
