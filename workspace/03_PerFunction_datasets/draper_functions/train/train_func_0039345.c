rpc_C_GetObjectSize (CK_SESSION_HANDLE session, CK_OBJECT_HANDLE object,
                     CK_ULONG_PTR size)
{
	return_val_if_fail (size, CKR_ARGUMENTS_BAD);

	BEGIN_CALL_OR (C_GetObjectSize, CKR_SESSION_HANDLE_INVALID);
		IN_ULONG (session);
		IN_ULONG (object);
	PROCESS_CALL;
		OUT_ULONG (size);
	END_CALL;
}
