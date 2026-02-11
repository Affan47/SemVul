TCSP_ConvertMigrationBlob_Internal(TCS_CONTEXT_HANDLE hContext,
				   TCS_KEY_HANDLE parentHandle,
				   UINT32 inDataSize,
				   BYTE * inData,
				   UINT32 randomSize,
				   BYTE * random,
				   TPM_AUTH * parentAuth,
				   UINT32 * outDataSize,
				   BYTE ** outData)
{
	TSS_RESULT result;
	UINT32 paramSize;
	UINT64 offset = 0;
	TCPA_KEY_HANDLE keySlot;
	BYTE txBlob[TSS_TPM_TXBLOB_SIZE];

	LogDebug("ConvertMigBlob");
	if ((result = ctx_verify_context(hContext)))
		goto done;

	if (parentAuth != NULL) {
		LogDebug("Auth Used");
		if ((result = auth_mgr_check(hContext, &parentAuth->AuthHandle)))
			goto done;
	} else {
		LogDebug("No Auth");
	}
	if ((result = ensureKeyIsLoaded(hContext, parentHandle, &keySlot)))
		goto done;

	if ((result = tpm_rqu_build(TPM_ORD_ConvertMigrationBlob, &offset, txBlob, keySlot,
				    inDataSize, inData, randomSize, random, parentAuth)))
		return result;

	if ((result = req_mgr_submit_req(txBlob)))
		goto done;

	offset = 10;
	result = UnloadBlob_Header(txBlob, &paramSize);

	if (!result) {
		result = tpm_rsp_parse(TPM_ORD_ConvertMigrationBlob, txBlob, paramSize, outDataSize,
				       outData, parentAuth, NULL);
	}
	LogResult("***Leaving ConvertMigrationBlob with result ", result);
done:
	auth_mgr_release_auth(parentAuth, NULL, hContext);
	return result;
}
