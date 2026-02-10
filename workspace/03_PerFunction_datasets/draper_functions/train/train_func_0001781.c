Transport_OIAP(TSS_HCONTEXT    tspContext,
	       TCS_AUTHHANDLE* authHandle,
	       TPM_NONCE*      nonce0)
{
	TSS_RESULT result;
	UINT32 decLen = 0;
	BYTE *dec = NULL;
	UINT64 offset;
	TCS_HANDLE handlesLen = 0;

	if ((result = obj_context_transport_init(tspContext)))
		return result;

	LogDebugFn("Executing in a transport session");

	if ((result = obj_context_transport_execute(tspContext, TPM_ORD_OIAP, 0, NULL, NULL,
						    &handlesLen, NULL, NULL, NULL, &decLen, &dec)))
		return result;

	if (decLen != sizeof(TCS_AUTHHANDLE) + sizeof(TPM_NONCE))
		return TSPERR(TSS_E_INTERNAL_ERROR);

	offset = 0;
	Trspi_UnloadBlob_UINT32(&offset, authHandle, dec);
	Trspi_UnloadBlob_NONCE(&offset, dec, nonce0);

	return result;
}
