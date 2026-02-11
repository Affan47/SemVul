camel_cipher_context_sign_sync (CamelCipherContext *context,
                                const gchar *userid,
                                CamelCipherHash hash,
                                CamelMimePart *ipart,
                                CamelMimePart *opart,
                                GCancellable *cancellable,
                                GError **error)
{
	CamelCipherContextClass *class;
	gboolean success;

	g_return_val_if_fail (CAMEL_IS_CIPHER_CONTEXT (context), FALSE);

	class = CAMEL_CIPHER_CONTEXT_GET_CLASS (context);
	g_return_val_if_fail (class->sign_sync != NULL, FALSE);

	CIPHER_LOCK (context);


	if (g_cancellable_set_error_if_cancelled (cancellable, error)) {
		CIPHER_UNLOCK (context);
		return FALSE;
	}

	camel_operation_push_message (cancellable, _("Signing message"));

	success = class->sign_sync (
		context, userid, hash, ipart, opart, cancellable, error);
	CAMEL_CHECK_GERROR (context, sign_sync, success, error);

	camel_operation_pop_message (cancellable);

	CIPHER_UNLOCK (context);

	return success;
}
