gcr_certificate_request_capable (GckObject *private_key,
                                 GCancellable *cancellable,
                                 GError **error)
{
	g_return_val_if_fail (GCK_IS_OBJECT (private_key), FALSE);
	g_return_val_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable), FALSE);
	g_return_val_if_fail (error == NULL || *error == NULL, FALSE);

	return _gcr_key_mechanisms_check (private_key, ALL_MECHANISMS,
	                                  G_N_ELEMENTS (ALL_MECHANISMS),
	                                 CKA_SIGN, cancellable, error);
}
