gcr_certificate_request_capable_async (GckObject *private_key,
                                       GCancellable *cancellable,
                                       GAsyncReadyCallback callback,
                                       gpointer user_data)
{
	g_return_if_fail (GCK_IS_OBJECT (private_key));
	g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));

	_gcr_key_mechanisms_check_async (private_key, ALL_MECHANISMS,
	                                 G_N_ELEMENTS (ALL_MECHANISMS),
	                                 CKA_SIGN, cancellable,
	                                 callback, user_data);
}
