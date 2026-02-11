RPC_GetPcrEvent_TP(struct host_table_entry *hte,
			       UINT32 PcrIndex,
			       UINT32 * pNumber,
			       TSS_PCR_EVENT ** ppEvent
    ) {
	TSS_RESULT result;
	BYTE lengthOnly = (ppEvent == NULL) ? TRUE : FALSE;

	initData(&hte->comm, 4);
	hte->comm.hdr.u.ordinal = TCSD_ORD_GETPCREVENT;
	LogDebugFn("TCS Context: 0x%x", hte->tcsContext);

	if (setData(TCSD_PACKET_TYPE_UINT32, 0, &hte->tcsContext, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);

	if (setData(TCSD_PACKET_TYPE_UINT32, 1, &PcrIndex, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);

	if (setData(TCSD_PACKET_TYPE_UINT32, 2, pNumber, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);

	if (setData(TCSD_PACKET_TYPE_BYTE, 3, &lengthOnly, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);

	result = sendTCSDPacket(hte);

	if (result == TSS_SUCCESS)
		result = hte->comm.hdr.u.result;

	if (result == TSS_SUCCESS) {
		if (getData(TCSD_PACKET_TYPE_UINT32, 0, pNumber, 0, &hte->comm)) {
			result = TSPERR(TSS_E_INTERNAL_ERROR);
			goto done;
		}

		if (ppEvent) {
			*ppEvent = malloc(sizeof(TSS_PCR_EVENT));
			if (*ppEvent == NULL) {
				LogError("malloc of %zd bytes failed.",
					 sizeof(TSS_PCR_EVENT));
				result = TSPERR(TSS_E_OUTOFMEMORY);
				goto done;
			}

			if (getData(TCSD_PACKET_TYPE_PCR_EVENT, 1, *ppEvent, 0, &hte->comm)) {
				free(*ppEvent);
				*ppEvent = NULL;
				result = TSPERR(TSS_E_INTERNAL_ERROR);
			}
		}
	}

done:
	return result;
}
