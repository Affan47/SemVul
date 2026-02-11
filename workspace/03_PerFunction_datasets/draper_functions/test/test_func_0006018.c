gck_session_encrypt_full (GckSession *self, GckObject *key, GckMechanism *mechanism,
                           const guchar *input, gsize n_input, gsize *n_result,
                           GCancellable *cancellable, GError **error)
{
	GckModule *module = NULL;
	CK_FUNCTION_LIST_PTR funcs;
	guchar *ret;

	g_object_get (self, "module", &module, NULL);
	g_return_val_if_fail (module != NULL, NULL);

	funcs = gck_module_get_functions (module);
	g_return_val_if_fail (module != NULL, NULL);

	ret = crypt_sync (self, key, mechanism, input, n_input, n_result, cancellable, error,
	                  funcs->C_EncryptInit, funcs->C_Encrypt);

	g_object_unref (module);
	return ret;
}
