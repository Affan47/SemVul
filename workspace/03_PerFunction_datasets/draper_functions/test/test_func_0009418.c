rpc_C_SetPIN (CK_SESSION_HANDLE session, CK_UTF8CHAR_PTR old_pin,
              CK_ULONG old_pin_len, CK_UTF8CHAR_PTR new_pin, CK_ULONG new_pin_len)
{
	BEGIN_CALL_OR (C_SetPIN, CKR_SESSION_HANDLE_INVALID);
		IN_ULONG (session);
		IN_BYTE_ARRAY (old_pin, old_pin_len);
		IN_BYTE_ARRAY (new_pin, old_pin_len);
	PROCESS_CALL;
	END_CALL;
}
