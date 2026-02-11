gkm_session_C_UnwrapKey (GkmSession* self, CK_MECHANISM_PTR mechanism,
                         CK_OBJECT_HANDLE unwrapping_key, CK_BYTE_PTR wrapped_key,
                         CK_ULONG wrapped_key_len, CK_ATTRIBUTE_PTR template,
                         CK_ULONG count, CK_OBJECT_HANDLE_PTR key)
{
	GkmObject *wrapper = NULL;
	GkmObject *unwrapped = NULL;
	CK_RV rv;

	g_return_val_if_fail (GKM_IS_SESSION (self), CKR_SESSION_HANDLE_INVALID);
	if (!mechanism)
		return CKR_ARGUMENTS_BAD;
	if (!(!count || template))
		return CKR_ARGUMENTS_BAD;
	if (!key)
		return CKR_ARGUMENTS_BAD;

	rv = gkm_session_lookup_readable_object (self, unwrapping_key, &wrapper);
	if (rv == CKR_OBJECT_HANDLE_INVALID)
		return CKR_WRAPPING_KEY_HANDLE_INVALID;
	else if (rv != CKR_OK)
		return rv;


	template = g_memdup (template, count * sizeof (CK_ATTRIBUTE));

	rv = gkm_crypto_unwrap_key (self, mechanism, wrapper, wrapped_key,
	                            wrapped_key_len, template, count, &unwrapped);

	g_free (template);

	if (rv == CKR_OK) {
		*key = gkm_object_get_handle (unwrapped);
		g_object_unref (unwrapped);
	}

	return rv;
}
