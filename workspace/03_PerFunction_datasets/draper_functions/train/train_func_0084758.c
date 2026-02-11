RPC_SetCapability_TP(struct host_table_entry *hte,
		      TCPA_CAPABILITY_AREA capArea,
		      UINT32 subCapSize,
		      BYTE * subCap,
		      UINT32 valueSize,
		      BYTE * value,
		      TPM_AUTH * pOwnerAuth)
{
	TSS_RESULT result;

	initData(&hte->comm, 7);
	hte->comm.hdr.u.ordinal = TCSD_ORD_SETCAPABILITY;
	LogDebugFn("TCS Context: 0x%x", hte->tcsContext);

	if (setData(TCSD_PACKET_TYPE_UINT32, 0, &hte->tcsContext, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_UINT32, 1, &capArea, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_UINT32, 2, &subCapSize, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_PBYTE, 3, subCap, subCapSize, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_UINT32, 4, &valueSize, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_PBYTE, 5, value, valueSize, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (pOwnerAuth) {
		if (setData(TCSD_PACKET_TYPE_AUTH, 6, pOwnerAuth, 0, &hte->comm))
			return TSPERR(TSS_E_INTERNAL_ERROR);
	}

	result = sendTCSDPacket(hte);

	if (result == TSS_SUCCESS)
		result = hte->comm.hdr.u.result;

	if (result == TSS_SUCCESS) {
		if (getData(TCSD_PACKET_TYPE_AUTH, 0, pOwnerAuth, 0, &hte->comm))
			result = TSPERR(TSS_E_INTERNAL_ERROR);
	}

	return result;
}
