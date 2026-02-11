TCSP_Sign_Internal(TCS_CONTEXT_HANDLE hContext,
		   TCS_KEY_HANDLE keyHandle,
		   UINT32 areaToSignSize,
		   BYTE * areaToSign,
		   TPM_AUTH * privAuth,
		   UINT32 * sigSize,
		   BYTE ** sig
    )
{
	UINT64 offset = 0;
	UINT32 paramSize;
	TSS_RESULT result;
	TCPA_KEY_HANDLE keySlot;
	BYTE txBlob[TSS_TPM_TXBLOB_SIZE];

	LogDebug("Entering Sign");
	if ((result = ctx_verify_context(hContext)))
		return result;

	if (privAuth != NULL) {
		LogDebug("Auth Used");
		if ((result = auth_mgr_check(hContext, &privAuth->AuthHandle)))
			goto done;
	} else {
		LogDebug("No Auth");
	}

	if ((result = ensureKeyIsLoaded(hContext, keyHandle, &keySlot)))
		goto done;

	if ((result = tpm_rqu_build(TPM_ORD_Sign, &offset, txBlob, keySlot, areaToSignSize,
				    areaToSign, privAuth)))
		return result;

	if ((result = req_mgr_submit_req(txBlob)))
		goto done;

	result = UnloadBlob_Header(txBlob, &paramSize);
	if (!result) {
		result = tpm_rsp_parse(TPM_ORD_Sign, txBlob, paramSize, sigSize, sig, privAuth,
				       NULL);
	}
	LogResult("sign", result);
done:
	auth_mgr_release_auth(privAuth, NULL, hContext);
	return result;
}
