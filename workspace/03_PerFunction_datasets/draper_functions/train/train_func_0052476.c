tcs_wrap_CreateMaintenanceArchive(struct tcsd_thread_data *data)
{
	TCS_CONTEXT_HANDLE hContext;
	TSS_RESULT result;
	TPM_AUTH ownerAuth;
	TSS_BOOL generateRandom;
	UINT32 randomSize, archiveSize;
	BYTE *random, *archive;

	if (getData(TCSD_PACKET_TYPE_UINT32, 0, &hContext, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	if ((result = ctx_verify_context(hContext)))
		goto done;

	LogDebugFn("thread %ld context %x", THREAD_ID, hContext);

	if (getData(TCSD_PACKET_TYPE_BOOL, 1, &generateRandom, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	if (getData(TCSD_PACKET_TYPE_AUTH, 2, &ownerAuth, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	MUTEX_LOCK(tcsp_lock);

	result = TCSP_CreateMaintenanceArchive_Internal(hContext, generateRandom, &ownerAuth,
							&randomSize, &random, &archiveSize,
							&archive);

	MUTEX_UNLOCK(tcsp_lock);

	if (result == TSS_SUCCESS) {
		initData(&data->comm, 5);
		if (setData(TCSD_PACKET_TYPE_AUTH, 0, &ownerAuth, 0, &data->comm)) {
			free(random);
			free(archive);
			return TCSERR(TSS_E_INTERNAL_ERROR);
		}

		if (setData(TCSD_PACKET_TYPE_UINT32, 1, &randomSize, 0, &data->comm)) {
			free(random);
			free(archive);
			return TCSERR(TSS_E_INTERNAL_ERROR);
		}
		if (setData(TCSD_PACKET_TYPE_PBYTE, 2, random, randomSize, &data->comm)) {
			free(random);
			free(archive);
			return TCSERR(TSS_E_INTERNAL_ERROR);
		}

		if (setData(TCSD_PACKET_TYPE_UINT32, 3, &archiveSize, 0, &data->comm)) {
			free(random);
			free(archive);
			return TCSERR(TSS_E_INTERNAL_ERROR);
		}
		if (setData(TCSD_PACKET_TYPE_PBYTE, 4, archive, archiveSize, &data->comm)) {
			free(random);
			free(archive);
			return TCSERR(TSS_E_INTERNAL_ERROR);
		}

		free(random);
		free(archive);
	} else
done:		initData(&data->comm, 0);

	data->comm.hdr.u.result = result;

	return TSS_SUCCESS;
}
