TCSP_OwnerReadPubek_Internal(TCS_CONTEXT_HANDLE hContext,
			     TPM_AUTH * ownerAuth,
			     UINT32 * pubEndorsementKeySize,
			     BYTE ** pubEndorsementKey)
{
	UINT32 paramSize;
	TSS_RESULT result;
	UINT64 offset = 0;
	BYTE txBlob[TSS_TPM_TXBLOB_SIZE];

	LogDebug("Entering OwnerReadPubek");

	if ((result = ctx_verify_context(hContext)))
		goto done;

	if ((result = auth_mgr_check(hContext, &ownerAuth->AuthHandle)))
		goto done;

	if ((result = tpm_rqu_build(TPM_ORD_OwnerReadPubek, &offset, txBlob, ownerAuth)))
		goto done;

	if ((result = req_mgr_submit_req(txBlob)))
		goto done;

	result = UnloadBlob_Header(txBlob, &paramSize);

	if (!result) {
		result = tpm_rsp_parse(TPM_ORD_OwnerReadPubek, txBlob, paramSize,
				       pubEndorsementKeySize, pubEndorsementKey, ownerAuth);
	}
	LogResult("Owner Read Pubek", result);
done:
	auth_mgr_release_auth(ownerAuth, NULL, hContext);
	return result;
}
