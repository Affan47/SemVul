canILoadThisKey(TCPA_KEY_PARMS *parms, TSS_BOOL *b)
{
	UINT16 subCapLength;
	UINT64 offset;
	BYTE subCap[100];
	TCPA_RESULT result;
	UINT32 respDataLength;
	BYTE *respData;

	offset = 0;
	LoadBlob_KEY_PARMS(&offset, subCap, parms);
	subCapLength = offset;

	if ((result = TCSP_GetCapability_Internal(InternalContext, TCPA_CAP_CHECK_LOADED,
						  subCapLength, subCap, &respDataLength,
						  &respData))) {
		*b = FALSE;
		LogDebugFn("NO");
		return result;
	}

	*b = respData[0];
	free(respData);
	LogDebugFn("%s", *b ? "YES" : "NO");

	return TSS_SUCCESS;
}
