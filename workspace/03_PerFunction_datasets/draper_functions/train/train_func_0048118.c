TCSP_FlushSpecific_Common(UINT32 tpmResHandle, TPM_RESOURCE_TYPE resourceType)
{
	UINT64 offset = 0;
	UINT32 paramSize;
	TSS_RESULT result;
	BYTE txBlob[TSS_TPM_TXBLOB_SIZE];

	if ((result = tpm_rqu_build(TPM_ORD_FlushSpecific, &offset, txBlob, tpmResHandle,
				    resourceType)))
		return result;

	if ((result = req_mgr_submit_req(txBlob)))
		return result;

	result = UnloadBlob_Header(txBlob, &paramSize);
	if (!result) {
		result = tpm_rsp_parse(TPM_ORD_FlushSpecific, txBlob, paramSize, NULL);
	}

	return result;
}
