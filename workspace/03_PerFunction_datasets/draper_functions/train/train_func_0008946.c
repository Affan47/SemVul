gdata_authorizer_refresh_authorization_async (GDataAuthorizer *self, GCancellable *cancellable, GAsyncReadyCallback callback, gpointer user_data)
{
	GDataAuthorizerInterface *iface;

	g_return_if_fail (GDATA_IS_AUTHORIZER (self));
	g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));

	iface = GDATA_AUTHORIZER_GET_IFACE (self);


	g_assert ((iface->refresh_authorization_async == NULL && iface->refresh_authorization_finish == NULL) ||
	          (iface->refresh_authorization_async != NULL && iface->refresh_authorization_finish != NULL));

	if (iface->refresh_authorization_async != NULL) {

		iface->refresh_authorization_async (self, cancellable, callback, user_data);
	} else if (iface->refresh_authorization != NULL) {

		GSimpleAsyncResult *result = g_simple_async_result_new (G_OBJECT (self), callback, user_data,
		                                                        gdata_authorizer_refresh_authorization_async);
		g_simple_async_result_run_in_thread (result, (GSimpleAsyncThreadFunc) refresh_authorization_thread, G_PRIORITY_DEFAULT, cancellable);
		g_object_unref (result);

		return;
	} else {

		GSimpleAsyncResult *result = g_simple_async_result_new (G_OBJECT (self), callback, user_data,
		                                                        gdata_authorizer_refresh_authorization_async);
		g_simple_async_result_complete_in_idle (result);
		g_object_unref (result);

		return;
	}
}
