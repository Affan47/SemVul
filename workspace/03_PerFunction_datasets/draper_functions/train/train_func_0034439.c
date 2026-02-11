TCSP_Delegate_ReadTable_Internal(TCS_CONTEXT_HANDLE hContext,
				 UINT32 *familyTableSize,
				 BYTE **familyTable,
				 UINT32 *delegateTableSize,
				 BYTE **delegateTable)
{
	TSS_RESULT result;
	UINT64 offset = 0;
	UINT32 paramSize;
	BYTE txBlob[TSS_TPM_TXBLOB_SIZE];

	LogDebugFn("Enter");

	if ((result = ctx_verify_context(hContext)))
		return result;

	if ((result = tpm_rqu_build(TPM_ORD_Delegate_ReadTable, &offset, txBlob, NULL)))
		return result;

	if ((result = req_mgr_submit_req(txBlob)))
		return result;

	result = UnloadBlob_Header(txBlob, &paramSize);
	if (!result) {
		result = tpm_rsp_parse(TPM_ORD_Delegate_ReadTable, txBlob, paramSize,
				       familyTableSize, familyTable, delegateTableSize,
				       delegateTable, NULL, NULL);
	}

	LogResult("Delegate_ReadTable", result);

	return result;
}
