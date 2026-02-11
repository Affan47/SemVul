RPC_GetCredential_TP(struct host_table_entry *hte,
		     UINT32 ulCredentialType,
		     UINT32 ulCredentialAccessMode,
		     UINT32 * pulCredentialSize,
		     BYTE ** prgbCredentialData)
{
	TSS_RESULT result;

	initData(&hte->comm, 3);
	hte->comm.hdr.u.ordinal = TCSD_ORD_GETCREDENTIAL;
	LogDebugFn("TCS Context: 0x%x", hte->tcsContext);

	if (setData(TCSD_PACKET_TYPE_UINT32, 0, &hte->tcsContext, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_UINT32, 1, &ulCredentialType, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_UINT32, 2, &ulCredentialAccessMode, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);

	result = sendTCSDPacket(hte);

	if (result == TSS_SUCCESS)
		result = hte->comm.hdr.u.result;

	if (result == TSS_SUCCESS) {
		if (getData(TCSD_PACKET_TYPE_UINT32, 0, pulCredentialSize, 0, &hte->comm)) {
			return TSPERR(TSS_E_INTERNAL_ERROR);
		}

		*prgbCredentialData = (BYTE *) malloc(*pulCredentialSize);
		if (*prgbCredentialData == NULL) {
			LogError("malloc of %u bytes failed.", *pulCredentialSize);
			return TSPERR(TSS_E_OUTOFMEMORY);
		}

		if (getData(TCSD_PACKET_TYPE_PBYTE, 1, *prgbCredentialData,
			    *pulCredentialSize, &hte->comm)) {
			free(*prgbCredentialData);
			result = TSPERR(TSS_E_INTERNAL_ERROR);
                }
	}
	return result;
}
