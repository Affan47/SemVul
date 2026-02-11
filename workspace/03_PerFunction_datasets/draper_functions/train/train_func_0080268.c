gkm_module_C_SetPIN (GkmModule* self, CK_SESSION_HANDLE handle, CK_UTF8CHAR_PTR old_pin,
                     CK_ULONG old_pin_len, CK_UTF8CHAR_PTR new_pin, CK_ULONG new_pin_len)
{
	GkmSession *session;
	Apartment *apt;
	CK_ULONG apt_id;

	g_return_val_if_fail (GKM_IS_MODULE (self), CKR_CRYPTOKI_NOT_INITIALIZED);

	session = gkm_module_lookup_session (self, handle);
	if (session == NULL)
		return CKR_SESSION_HANDLE_INVALID;


	apt_id = gkm_session_get_apartment (session);
	apt = lookup_apartment (self, apt_id);
	g_return_val_if_fail (apt, CKR_GENERAL_ERROR);

	return gkm_module_login_change (self, apt_id, old_pin, old_pin_len, new_pin, new_pin_len);
}
