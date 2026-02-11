TCSP_PhysicalPresence_Internal(TCS_CONTEXT_HANDLE hContext,
			TCPA_PHYSICAL_PRESENCE fPhysicalPresence)
{
	UINT64 offset = 0;
	UINT32 paramSize;
	TSS_RESULT result = TCSERR(TSS_E_NOTIMPL);
	BYTE txBlob[TSS_TPM_TXBLOB_SIZE];
	char runlevel;

	runlevel = platform_get_runlevel();

	if (runlevel != 's' && runlevel != 'S' && runlevel != '1') {
		LogInfo("Physical Presence command denied: Must be in single"
				" user mode.");
		return TCSERR(TSS_E_NOTIMPL);
	}

	if ((result = ctx_verify_context(hContext)))
		return result;

	if ((result = tpm_rqu_build(TSC_ORD_PhysicalPresence, &offset, txBlob, fPhysicalPresence)))
		return result;

	if ((result = req_mgr_submit_req(txBlob)))
		return result;

	return UnloadBlob_Header(txBlob, &paramSize);
}
