RPC_GetPcrEventLog_TP(struct host_table_entry *hte,
				  UINT32 * pEventCount,
				  TSS_PCR_EVENT ** ppEvents
    ) {
	TSS_RESULT result;
	int i, j;

	initData(&hte->comm, 1);
	hte->comm.hdr.u.ordinal = TCSD_ORD_GETPCREVENTLOG;
	LogDebugFn("TCS Context: 0x%x", hte->tcsContext);

	if (setData(TCSD_PACKET_TYPE_UINT32, 0, &hte->tcsContext, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);

	result = sendTCSDPacket(hte);

	if (result == TSS_SUCCESS)
		result = hte->comm.hdr.u.result;

	if (result == TSS_SUCCESS) {
		if (getData(TCSD_PACKET_TYPE_UINT32, 0, pEventCount, 0, &hte->comm)) {
			result = TSPERR(TSS_E_INTERNAL_ERROR);
			goto done;
		}

		if (*pEventCount > 0) {
			*ppEvents = calloc_tspi(hte->tspContext,
						sizeof(TSS_PCR_EVENT) * (*pEventCount));
			if (*ppEvents == NULL) {
				LogError("malloc of %zd bytes failed.",
					 sizeof(TSS_PCR_EVENT) * (*pEventCount));
				result = TSPERR(TSS_E_OUTOFMEMORY);
				goto done;
			}

			i = 1;
			for (j = 0; (UINT32)j < (*pEventCount); j++) {
				if (getData(TCSD_PACKET_TYPE_PCR_EVENT, i++, &((*ppEvents)[j]), 0, &hte->comm)) {
					free(*ppEvents);
					*ppEvents = NULL;
					result = TSPERR(TSS_E_INTERNAL_ERROR);
					goto done;
				}
			}
		} else {
			*ppEvents = NULL;
		}
	}

done:
	return result;
}
