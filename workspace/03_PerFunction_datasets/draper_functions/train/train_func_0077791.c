RPC_TakeOwnership_TP(struct host_table_entry *hte,
		      UINT16 protocolID,
		      UINT32 encOwnerAuthSize,
		      BYTE * encOwnerAuth,
		      UINT32 encSrkAuthSize,
		      BYTE * encSrkAuth,
		      UINT32 srkInfoSize,
		      BYTE * srkInfo,
		      TPM_AUTH * ownerAuth,
		      UINT32 * srkKeySize,
		      BYTE ** srkKey)
{
	TSS_RESULT result;

	initData(&hte->comm, 9);
	hte->comm.hdr.u.ordinal = TCSD_ORD_TAKEOWNERSHIP;
	LogDebugFn("TCS Context: 0x%x", hte->tcsContext);

	if (setData(TCSD_PACKET_TYPE_UINT32, 0, &hte->tcsContext, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_UINT16, 1, &protocolID, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_UINT32, 2, &encOwnerAuthSize, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_PBYTE, 3, encOwnerAuth, encOwnerAuthSize, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_UINT32, 4, &encSrkAuthSize, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_PBYTE, 5, encSrkAuth, encSrkAuthSize, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_UINT32, 6, &srkInfoSize, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_PBYTE, 7, srkInfo, srkInfoSize, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_AUTH, 8, ownerAuth, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);

	result = sendTCSDPacket(hte);

	if (result == TSS_SUCCESS)
		result = hte->comm.hdr.u.result;

	if (result == TSS_SUCCESS) {
		if (getData(TCSD_PACKET_TYPE_AUTH, 0, ownerAuth, 0, &hte->comm)) {
			result = TSPERR(TSS_E_INTERNAL_ERROR);
			goto done;
		}
		if (getData(TCSD_PACKET_TYPE_UINT32, 1, srkKeySize, 0, &hte->comm)) {
			result = TSPERR(TSS_E_INTERNAL_ERROR);
			goto done;
		}

		*srkKey = (BYTE *) malloc(*srkKeySize);
		if (*srkKey == NULL) {
			LogError("malloc of %u bytes failed.", *srkKeySize);
			result = TSPERR(TSS_E_OUTOFMEMORY);
			goto done;
		}
		if (getData(TCSD_PACKET_TYPE_PBYTE, 2, *srkKey, *srkKeySize, &hte->comm)) {
			free(*srkKey);
			result = TSPERR(TSS_E_INTERNAL_ERROR);
		}
	}

done:
	return result;
}
