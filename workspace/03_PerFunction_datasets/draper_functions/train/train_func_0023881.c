rpc_C_WrapKey (CK_SESSION_HANDLE session, CK_MECHANISM_PTR mechanism,
               CK_OBJECT_HANDLE wrapping_key, CK_OBJECT_HANDLE key,
               CK_BYTE_PTR wrapped_key, CK_ULONG_PTR wrapped_key_len)
{
	return_val_if_fail (wrapped_key_len, CKR_ARGUMENTS_BAD);

	BEGIN_CALL_OR (C_WrapKey, CKR_SESSION_HANDLE_INVALID);
		IN_ULONG (session);
		IN_MECHANISM (mechanism);
		IN_ULONG (wrapping_key);
		IN_ULONG (key);
		IN_BYTE_BUFFER (wrapped_key, wrapped_key_len);
	PROCESS_CALL;
		OUT_BYTE_ARRAY (wrapped_key, wrapped_key_len);
	END_CALL;
}
