tcs_wrap_LoadKey2ByBlob(struct tcsd_thread_data *data)
{
	TCS_CONTEXT_HANDLE hContext;
	TCS_KEY_HANDLE hUnwrappingKey;
	UINT32 cWrappedKeyBlob;
	BYTE *rgbWrappedKeyBlob;
	TPM_AUTH auth;
	TCS_KEY_HANDLE phKeyTCSI;
	TPM_AUTH *pAuth;
	TSS_RESULT result;
	int i;

	if (getData(TCSD_PACKET_TYPE_UINT32, 0, &hContext, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	LogDebugFn("thread %ld context %x", THREAD_ID, hContext);

	if (getData(TCSD_PACKET_TYPE_UINT32, 1, &hUnwrappingKey, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);
	if (getData(TCSD_PACKET_TYPE_UINT32, 2, &cWrappedKeyBlob, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	rgbWrappedKeyBlob = calloc(1, cWrappedKeyBlob);
	if (rgbWrappedKeyBlob == NULL) {
		LogError("malloc of %d bytes failed.", cWrappedKeyBlob);
		return TCSERR(TSS_E_OUTOFMEMORY);
	}
	if (getData(TCSD_PACKET_TYPE_PBYTE, 3, rgbWrappedKeyBlob, cWrappedKeyBlob, &data->comm)) {
		free(rgbWrappedKeyBlob);
		return TCSERR(TSS_E_INTERNAL_ERROR);
	}
	result = getData(TCSD_PACKET_TYPE_AUTH, 4, &auth, 0, &data->comm);
	if (result == TSS_TCP_RPC_BAD_PACKET_TYPE)
		pAuth = NULL;
	else if (result) {
		free(rgbWrappedKeyBlob);
		return result;
	} else
		pAuth = &auth;

	MUTEX_LOCK(tcsp_lock);

	result = key_mgr_load_by_blob(hContext, hUnwrappingKey, cWrappedKeyBlob, rgbWrappedKeyBlob,
				      pAuth, &phKeyTCSI, NULL);

	if (!result)
		result = ctx_mark_key_loaded(hContext, phKeyTCSI);

	MUTEX_UNLOCK(tcsp_lock);

	free(rgbWrappedKeyBlob);

	if (result == TSS_SUCCESS) {
		i = 0;
		initData(&data->comm, 2);
		if (pAuth != NULL) {
			if (setData(TCSD_PACKET_TYPE_AUTH, i++, pAuth, 0, &data->comm)) {
				return TCSERR(TSS_E_INTERNAL_ERROR);
			}
		}
		if (setData(TCSD_PACKET_TYPE_UINT32, i++, &phKeyTCSI, 0, &data->comm)) {
			return TCSERR(TSS_E_INTERNAL_ERROR);
		}
	} else
		initData(&data->comm, 0);

	data->comm.hdr.u.result = result;

	return TSS_SUCCESS;
}
