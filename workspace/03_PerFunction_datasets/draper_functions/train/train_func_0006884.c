tcs_wrap_DirWriteAuth(struct tcsd_thread_data *data)
{
	TSS_RESULT result;
	TSS_HCONTEXT hContext;
	TCPA_DIRINDEX dirIndex;
	TCPA_DIGEST dirDigest;
	TPM_AUTH auth;

	if (getData(TCSD_PACKET_TYPE_UINT32, 0, &hContext, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	if ((result = ctx_verify_context(hContext)))
		goto done;

	LogDebugFn("thread %ld context %x", THREAD_ID, hContext);

	if (getData(TCSD_PACKET_TYPE_UINT32, 1, &dirIndex, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);
	if (getData(TCSD_PACKET_TYPE_DIGEST, 2, &dirDigest, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);
	if (getData(TCSD_PACKET_TYPE_AUTH, 3, &auth, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	MUTEX_LOCK(tcsp_lock);

	result = TCSP_DirWriteAuth_Internal(hContext, dirIndex, dirDigest, &auth);

	MUTEX_UNLOCK(tcsp_lock);

	if (result == TSS_SUCCESS) {
		initData(&data->comm, 1);
		if (setData(TCSD_PACKET_TYPE_AUTH, 0, &auth, 0, &data->comm)) {
			return TCSERR(TSS_E_INTERNAL_ERROR);
		}
	} else
done:		initData(&data->comm, 0);

	data->comm.hdr.u.result = result;

	return TSS_SUCCESS;
}
