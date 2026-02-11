OnMessageReceipt(RakNetGUID guid, uint32_t receiptId, bool messageArrived)
{

	if (messageArrived)
		FreeVarsAssociatedWithReceipt(guid, receiptId);
	else
		DirtyAndFreeVarsAssociatedWithReceipt(guid, receiptId);

}
