_secret_session_open (SecretService *service,
                      GCancellable *cancellable,
                      GAsyncReadyCallback callback,
                      gpointer user_data)
{
	GSimpleAsyncResult *res;
	OpenSessionClosure *closure;

	res = g_simple_async_result_new (G_OBJECT (service), callback, user_data,
	                                 _secret_session_open);
	closure = g_new (OpenSessionClosure, 1);
	closure->cancellable = cancellable ? g_object_ref (cancellable) : cancellable;
	closure->session = g_new0 (SecretSession, 1);
	g_simple_async_result_set_op_res_gpointer (res, closure, open_session_closure_free);

	g_dbus_proxy_call (G_DBUS_PROXY (service), "OpenSession",
#ifdef WITH_GCRYPT
	                   request_open_session_aes (closure->session),
	                   G_DBUS_CALL_FLAGS_NONE, -1,
	                   cancellable, on_service_open_session_aes,
#else
	                   request_open_session_plain (closure->session),
	                   G_DBUS_CALL_FLAGS_NONE, -1,
	                   cancellable, on_service_open_session_plain,
#endif
	                   g_object_ref (res));

	g_object_unref (res);
}
