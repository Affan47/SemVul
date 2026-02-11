rpc_C_WaitForSlotEvent (CK_FLAGS flags, CK_SLOT_ID_PTR slot, CK_VOID_PTR reserved)
{
	return_val_if_fail (slot, CKR_ARGUMENTS_BAD);

	BEGIN_CALL_OR (C_WaitForSlotEvent, CKR_DEVICE_REMOVED);
		IN_ULONG (flags);
	PROCESS_CALL;
		OUT_ULONG (slot);
	END_CALL;
}
