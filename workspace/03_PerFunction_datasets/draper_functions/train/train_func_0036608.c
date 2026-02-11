rpc_C_InitPIN (CK_SESSION_HANDLE session, CK_UTF8CHAR_PTR pin,
               CK_ULONG pin_len)
{
	BEGIN_CALL_OR (C_InitPIN, CKR_SESSION_HANDLE_INVALID);
		IN_ULONG (session);
		IN_BYTE_ARRAY (pin, pin_len);
	PROCESS_CALL;
	END_CALL;
}
