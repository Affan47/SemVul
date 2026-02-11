Transport_MakeIdentity2(TSS_HCONTEXT tspContext,
			TCPA_ENCAUTH identityAuth,
			TCPA_CHOSENID_HASH IDLabel_PrivCAHash,
			UINT32 idKeyInfoSize,
			BYTE * idKeyInfo,
			TPM_AUTH * pSrkAuth,
			TPM_AUTH * pOwnerAuth,
			UINT32 * idKeySize,
			BYTE ** idKey,
			UINT32 * pcIdentityBindingSize,
			BYTE ** prgbIdentityBinding)
{
	UINT64 offset;
	TSS_RESULT result;
	UINT32 handlesLen = 0, decLen, dataLen;
	BYTE *dec, *data;

	if ((result = obj_context_transport_init(tspContext)))
		return result;

	LogDebugFn("Executing in a transport session");

	dataLen = sizeof(TCPA_ENCAUTH) + sizeof(TCPA_CHOSENID_HASH) + idKeyInfoSize;
	if ((data = malloc(dataLen)) == NULL) {
		LogError("malloc of %u bytes failed", dataLen);
		return TSPERR(TSS_E_OUTOFMEMORY);
	}

	offset = 0;
	Trspi_LoadBlob(&offset, sizeof(TCPA_ENCAUTH), data, identityAuth.authdata);
	Trspi_LoadBlob(&offset, sizeof(TCPA_CHOSENID_HASH), data, IDLabel_PrivCAHash.digest);
	Trspi_LoadBlob(&offset, idKeyInfoSize, data, idKeyInfo);

	if ((result = obj_context_transport_execute(tspContext, TPM_ORD_MakeIdentity, dataLen,
						    data, NULL, &handlesLen, NULL, pSrkAuth,
						    pOwnerAuth, &decLen, &dec))) {
		free(data);
		return result;
	}
	free(data);

	offset = 0;
	UnloadBlob_TSS_KEY(&offset, dec, NULL);
	*idKeySize = offset;

	if ((*idKey = malloc(*idKeySize)) == NULL) {
		free(dec);
		LogError("malloc of %u bytes failed", *idKeySize);
		*idKeySize = 0;
		return TSPERR(TSS_E_OUTOFMEMORY);
	}

	offset = 0;
	Trspi_UnloadBlob(&offset, *idKeySize, dec, *idKey);

	Trspi_UnloadBlob_UINT32(&offset, pcIdentityBindingSize, dec);
	if ((*prgbIdentityBinding = malloc(*pcIdentityBindingSize)) == NULL) {
		free(dec);
		free(*idKey);
		*idKey = NULL;
		*idKeySize = 0;
		LogError("malloc of %u bytes failed", *pcIdentityBindingSize);
		*pcIdentityBindingSize = 0;
		return TSPERR(TSS_E_OUTOFMEMORY);
	}
	Trspi_UnloadBlob(&offset, *pcIdentityBindingSize, dec, *prgbIdentityBinding);
	free(dec);

	return result;
}
