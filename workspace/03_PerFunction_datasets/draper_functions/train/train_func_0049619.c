RPC_LoadKeyByUUID_TP(struct host_table_entry *hte,
				  TSS_UUID KeyUUID,
				  TCS_LOADKEY_INFO * pLoadKeyInfo,
				  TCS_KEY_HANDLE * phKeyTCSI
    ) {
	TSS_RESULT result;

	initData(&hte->comm, 3);
	hte->comm.hdr.u.ordinal = TCSD_ORD_LOADKEYBYUUID;
	LogDebugFn("TCS Context: 0x%x", hte->tcsContext);

	if (setData(TCSD_PACKET_TYPE_UINT32, 0, &hte->tcsContext, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);
	if (setData(TCSD_PACKET_TYPE_UUID, 1, &KeyUUID, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);

	if (pLoadKeyInfo != NULL) {
		if (setData(TCSD_PACKET_TYPE_LOADKEY_INFO, 2, pLoadKeyInfo, 0, &hte->comm))
			return TSPERR(TSS_E_INTERNAL_ERROR);
	}

	result = sendTCSDPacket(hte);

	if (result == TSS_SUCCESS)
		result = hte->comm.hdr.u.result;

	if (result == TSS_SUCCESS) {
		if (getData(TCSD_PACKET_TYPE_UINT32, 0, phKeyTCSI, 0, &hte->comm))
			result = TSPERR(TSS_E_INTERNAL_ERROR);

		LogDebugFn("TCS key handle: 0x%x", *phKeyTCSI);
	} else if (pLoadKeyInfo && (result == (TCS_E_KM_LOADFAILED | TSS_LAYER_TCS))) {
		if (getData(TCSD_PACKET_TYPE_LOADKEY_INFO, 0, pLoadKeyInfo, 0, &hte->comm))
			result = TSPERR(TSS_E_INTERNAL_ERROR);
	}

	return result;
}
