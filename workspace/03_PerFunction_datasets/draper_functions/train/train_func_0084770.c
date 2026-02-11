RPC_Delegate_ReadTable_TP(struct host_table_entry *hte,
			  UINT32 *familyTableSize,
			  BYTE **familyTable,
			  UINT32 *delegateTableSize,
			  BYTE **delegateTable)
{
	TSS_RESULT result;

	initData(&hte->comm, 1);
	hte->comm.hdr.u.ordinal = TCSD_ORD_DELEGATE_READTABLE;
	LogDebugFn("TCS Context: 0x%x", hte->tcsContext);

	if (setData(TCSD_PACKET_TYPE_UINT32, 0, &hte->tcsContext, 0, &hte->comm))
		return TSPERR(TSS_E_INTERNAL_ERROR);

	result = sendTCSDPacket(hte);

	if (result == TSS_SUCCESS)
		result = hte->comm.hdr.u.result;

	if (result == TSS_SUCCESS) {
		if (getData(TCSD_PACKET_TYPE_UINT32, 0, familyTableSize, 0, &hte->comm))
			return TSPERR(TSS_E_INTERNAL_ERROR);
		*familyTable = (BYTE *)malloc(*familyTableSize);
		if (*familyTable == NULL) {
			LogError("malloc of %u bytes failed.", *familyTableSize);
			return TSPERR(TSS_E_OUTOFMEMORY);
		}
		if (getData(TCSD_PACKET_TYPE_PBYTE, 1, *familyTable, *familyTableSize, &hte->comm)) {
			free(*familyTable);
			return TSPERR(TSS_E_INTERNAL_ERROR);
		}

		if (getData(TCSD_PACKET_TYPE_UINT32, 2, delegateTableSize, 0, &hte->comm)) {
			free(*familyTable);
			return TSPERR(TSS_E_INTERNAL_ERROR);
		}
		*delegateTable = (BYTE *)malloc(*delegateTableSize);
		if (*delegateTable == NULL) {
			free(*familyTable);
			LogError("malloc of %u bytes failed.", *delegateTableSize);
			return TSPERR(TSS_E_OUTOFMEMORY);
		}
		if (getData(TCSD_PACKET_TYPE_PBYTE, 3, *delegateTable, *delegateTableSize, &hte->comm)) {
			free(*familyTable);
			free(*delegateTable);
			return TSPERR(TSS_E_INTERNAL_ERROR);
		}
	}

	return result;
}
