gcr_pkcs11_certificate_lookup_issuer_async (GcrCertificate *certificate, GCancellable *cancellable,
                                            GAsyncReadyCallback callback, gpointer user_data)
{
	GSimpleAsyncResult *async;
	lookup_issuer_closure *closure;

	g_return_if_fail (GCR_IS_CERTIFICATE (certificate));

	async = g_simple_async_result_new (G_OBJECT (certificate), callback, user_data,
	                                   gcr_pkcs11_certificate_lookup_issuer_async);
	closure = g_new0 (lookup_issuer_closure, 1);
	closure->search = prepare_lookup_certificate_issuer (certificate);
	g_return_if_fail (closure->search);
	g_simple_async_result_set_op_res_gpointer (async, closure, lookup_issuer_free);

	g_simple_async_result_run_in_thread (async, thread_lookup_certificate,
	                                     G_PRIORITY_DEFAULT, cancellable);

	g_object_unref (async);
}
