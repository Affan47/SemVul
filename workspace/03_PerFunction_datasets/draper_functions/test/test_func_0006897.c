secret_item_load_secret (SecretItem *self,
                         GCancellable *cancellable,
                         GAsyncReadyCallback callback,
                         gpointer user_data)
{
	GSimpleAsyncResult *res;
	LoadClosure *closure;

	g_return_if_fail (SECRET_IS_ITEM (self));
	g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));

	res = g_simple_async_result_new (G_OBJECT (self), callback,
	                                 user_data, secret_item_load_secret);
	closure = g_slice_new0 (LoadClosure);
	closure->cancellable = cancellable ? g_object_ref (cancellable) : NULL;
	g_simple_async_result_set_op_res_gpointer (res, closure, load_closure_free);

	secret_service_ensure_session (self->pv->service, cancellable,
	                               on_load_ensure_session,
	                               g_object_ref (res));

	g_object_unref (res);
}
