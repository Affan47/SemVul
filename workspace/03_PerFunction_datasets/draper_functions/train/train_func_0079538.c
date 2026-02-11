Transport_SetCapability(TSS_HCONTEXT tspContext,
			TCPA_CAPABILITY_AREA capArea,
			UINT32 subCapSize,
			BYTE * subCap,
			UINT32 valueSize,
			BYTE * value,
			TPM_AUTH *ownerAuth)
{
	TSS_RESULT result;
	UINT32 dataLen;
	UINT64 offset;
	TCS_HANDLE handlesLen = 0;
	BYTE *data;

	if ((result = obj_context_transport_init(tspContext)))
		return result;

	LogDebugFn("Executing in a transport session");

	dataLen = (3 * sizeof(UINT32)) + subCapSize + valueSize;
	if ((data = malloc(dataLen)) == NULL) {
		LogError("malloc of %u bytes failed", dataLen);
		return TSPERR(TSS_E_OUTOFMEMORY);
	}

	offset = 0;
	Trspi_LoadBlob_UINT32(&offset, capArea, data);
	Trspi_LoadBlob_UINT32(&offset, subCapSize, data);
	Trspi_LoadBlob(&offset, subCapSize, data, subCap);
	Trspi_LoadBlob_UINT32(&offset, valueSize, data);
	Trspi_LoadBlob(&offset, valueSize, data, value);

	result = obj_context_transport_execute(tspContext, TPM_ORD_SetCapability, dataLen, data,
					       NULL, &handlesLen, NULL, NULL, NULL, NULL, NULL);

	free(data);
	return result;
}
