RPC_Sign_TP(struct host_table_entry *hte,
			 TCS_KEY_HANDLE keyHandle,
			 UINT32 areaToSignSize,
			 BYTE * areaToSign,
			 TPM_AUTH * privAuth,
			 UINT32 * sigSize,
			 BYTE ** sig
    ) {
	TSS_RESULT result;
	int i;

	initData(&hte->comm, 5);
	hte->comm.hdr.u.ordinal = TCSD_ORD_SIGN;
	LogDebugFn("TCS Context: 0x%x", hte->tcsContext);

	if (setData(TCSD_PACKET_TYPE_UINT32, 0, &hte->tcsContext, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_UINT32, 1, &keyHandle, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_UINT32, 2, &areaToSignSize, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_PBYTE, 3, areaToSign, areaToSignSize, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);

	if (privAuth) {
		if (setData(TCSD_PACKET_TYPE_AUTH, 4, privAuth, 0, &hte->comm))
			return TSPERR(TSS_E_INTERNAL_ERROR);
	}

	result = sendTCSDPacket(hte);

	if (result == TSS_SUCCESS)
		result = hte->comm.hdr.u.result;

	if (result == TSS_SUCCESS) {
		i = 0;
		if (privAuth) {
			if (getData(TCSD_PACKET_TYPE_AUTH, i++, privAuth, 0, &hte->comm)) {
				result = TSPERR(TSS_E_INTERNAL_ERROR);
				goto done;
			}
		}
		if (getData(TCSD_PACKET_TYPE_UINT32, i++, sigSize, 0, &hte->comm)) {
			result = TSPERR(TSS_E_INTERNAL_ERROR);
			goto done;
		}

		*sig = (BYTE *) malloc(*sigSize);
		if (*sig == NULL) {
			LogError("malloc of %u bytes failed.", *sigSize);
			result = TSPERR(TSS_E_OUTOFMEMORY);
			goto done;
		}
		if (getData(TCSD_PACKET_TYPE_PBYTE, i++, *sig, *sigSize, &hte->comm)) {
			result = free_tspi(hte->tspContext, *sig);
			if (result == TSS_SUCCESS)
				result = TSPERR(TSS_E_INTERNAL_ERROR);
			else
				free(*sig);
		}
	}

done:
	return result;
}
