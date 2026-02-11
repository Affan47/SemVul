RPC_Delegate_CreateKeyDelegation_TP(struct host_table_entry *hte,
				    TCS_KEY_HANDLE hKey,
				    UINT32 publicInfoSize,
				    BYTE *publicInfo,
				    TPM_ENCAUTH *encDelAuth,
				    TPM_AUTH *keyAuth,
				    UINT32 *blobSize,
				    BYTE **blob)
{
	TSS_RESULT result;
	int i;

	initData(&hte->comm, 8);
	hte->comm.hdr.u.ordinal = TCSD_ORD_DELEGATE_CREATEKEYDELEGATION;
	LogDebugFn("TCS Context: 0x%x", hte->tcsContext);

	if (setData(TCSD_PACKET_TYPE_UINT32, 0, &hte->tcsContext, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_UINT32, 1, &hKey, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_UINT32, 2, &publicInfoSize, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_PBYTE, 3, publicInfo, publicInfoSize, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_ENCAUTH, 4, encDelAuth, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (keyAuth) {
		if (setData(TCSD_PACKET_TYPE_AUTH, 5, keyAuth, 0, &hte->comm))
			return TSPERR(TSS_E_INTERNAL_ERROR);
	} else {
		TPM_AUTH nullAuth;

		__tspi_memset(&nullAuth, 0, sizeof(TPM_AUTH));
		if (setData(TCSD_PACKET_TYPE_AUTH, 5, &nullAuth, 0, &hte->comm))
			return TSPERR(TSS_E_INTERNAL_ERROR);
	}

	result = sendTCSDPacket(hte);

	if (result == TSS_SUCCESS)
		result = hte->comm.hdr.u.result;

	if (result == TSS_SUCCESS) {
		i = 0;
		if (keyAuth) {
			if (getData(TCSD_PACKET_TYPE_AUTH, i++, keyAuth, 0, &hte->comm))
				return TSPERR(TSS_E_INTERNAL_ERROR);
		}
		if (getData(TCSD_PACKET_TYPE_UINT32, i++, blobSize, 0, &hte->comm))
			return TSPERR(TSS_E_INTERNAL_ERROR);
		*blob = (BYTE *)malloc(*blobSize);
		if (*blob == NULL) {
			LogError("malloc of %u bytes failed.", *blobSize);
			return TSPERR(TSS_E_OUTOFMEMORY);
		}
		if (getData(TCSD_PACKET_TYPE_PBYTE, i++, *blob, *blobSize, &hte->comm)) {
			free(*blob);
			return TSPERR(TSS_E_INTERNAL_ERROR);
		}
	}

	return result;
}
