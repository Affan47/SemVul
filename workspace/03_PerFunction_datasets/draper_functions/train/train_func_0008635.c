RPC_GetTestResult_TP(struct host_table_entry *hte,
		      UINT32 * outDataSize,
		      BYTE ** outData)
{
	TSS_RESULT result;

	initData(&hte->comm, 1);
	hte->comm.hdr.u.ordinal = TCSD_ORD_GETTESTRESULT;
	LogDebugFn("TCS Context: 0x%x", hte->tcsContext);

	LogDebug("RPC_GetTestResult_TP");
	if (setData(TCSD_PACKET_TYPE_UINT32, 0, &hte->tcsContext, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);

	result = sendTCSDPacket(hte);

	if (result == TSS_SUCCESS)
		result = hte->comm.hdr.u.result;

	if (result == TSS_SUCCESS) {
		LogDebug("sendTCSDPacket succeeded");
		if (getData(TCSD_PACKET_TYPE_UINT32, 0, outDataSize, 0, &hte->comm)) {
			result = TSPERR(TSS_E_INTERNAL_ERROR);
			goto done;
		}

		*outData = malloc(*outDataSize);
		if (*outData == NULL) {
			LogError("malloc of %u bytes failed.", *outDataSize);
			result = TSPERR(TSS_E_OUTOFMEMORY);
			goto done;
		}

		if (getData(TCSD_PACKET_TYPE_PBYTE, 1, *outData, *outDataSize, &hte->comm)) {
			free(*outData);
			*outData = NULL;
			result = TSPERR(TSS_E_INTERNAL_ERROR);
		}
	}
	LogDebug("RPC_GetTestResult_TP exit");

done:
	return result;
}
