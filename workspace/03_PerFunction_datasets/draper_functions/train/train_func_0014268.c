Tspi_TPM_ReadCurrentTicks(TSS_HTPM           hTPM,
			  TPM_CURRENT_TICKS* tickCount)
{
	TSS_RESULT result;
	TSS_HCONTEXT tspContext;
	UINT32 tcLen;
	BYTE *tc;
	UINT64 offset;

	if (tickCount == NULL)
		return TSPERR(TSS_E_BAD_PARAMETER);

	if ((result = obj_tpm_get_tsp_context(hTPM, &tspContext)))
		return result;

	if ((result = TCS_API(tspContext)->ReadCurrentTicks(tspContext, &tcLen, &tc)))
		return result;

	offset = 0;
	Trspi_UnloadBlob_CURRENT_TICKS(&offset, tc, tickCount);
	free(tc);

	return result;
}
