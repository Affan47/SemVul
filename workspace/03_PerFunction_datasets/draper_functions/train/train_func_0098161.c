Transport_Delegate_CreateOwnerDelegation(TSS_HCONTEXT tspContext,
					 TSS_BOOL increment,
					 UINT32 publicInfoSize,
					 BYTE *publicInfo,
					 TPM_ENCAUTH *encDelAuth,
					 TPM_AUTH *ownerAuth,
					 UINT32 *blobSize,
					 BYTE **blob)
{
	TSS_RESULT result;
	UINT32 handlesLen = 0, decLen, dataLen;
	UINT64 offset;
	BYTE *data, *dec = NULL;

	if ((result = obj_context_transport_init(tspContext)))
		return result;

	LogDebugFn("Executing in a transport session");

	dataLen = sizeof(TSS_BOOL) + publicInfoSize + sizeof(TPM_ENCAUTH);
	if ((data = malloc(dataLen)) == NULL) {
		LogError("malloc of %u bytes failed", dataLen);
		return TSPERR(TSS_E_OUTOFMEMORY);
	}

	offset = 0;
	Trspi_LoadBlob_BOOL(&offset, increment, data);
	Trspi_LoadBlob(&offset, publicInfoSize, data, publicInfo);
	Trspi_LoadBlob(&offset, sizeof(TPM_ENCAUTH), data, encDelAuth->authdata);

	if ((result = obj_context_transport_execute(tspContext,
						    TPM_ORD_Delegate_CreateOwnerDelegation, dataLen,
						    data, NULL, &handlesLen, NULL, ownerAuth,
						    NULL, &decLen, &dec))) {
		free(data);
		return result;
	}
	free(data);

	offset = 0;
	Trspi_UnloadBlob_UINT32(&offset, blobSize, dec);

	if ((*blob = malloc(*blobSize)) == NULL) {
		free(dec);
		LogError("malloc of %u bytes failed", *blobSize);
		*blobSize = 0;
		return TSPERR(TSS_E_OUTOFMEMORY);
	}
	Trspi_UnloadBlob(&offset, *blobSize, dec, *blob);

	free(dec);

	return result;
}
