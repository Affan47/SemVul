obj_delfamily_set_locked(TSS_HDELFAMILY hFamily, TSS_BOOL state, TSS_BOOL setInTpm)
{
	struct tsp_object *obj;
	struct tr_delfamily_obj *delfamily;
	TSS_HTPM hTpm;
	UINT32 opDataSize;
	BYTE opData[8];
	UINT32 outDataSize;
	BYTE *outData = NULL;
	UINT64 offset;
	TSS_RESULT result = TSS_SUCCESS;

	if ((obj = obj_list_get_obj(&delfamily_list, hFamily)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	delfamily = (struct tr_delfamily_obj *)obj->data;

	if (setInTpm) {
		if ((result = obj_tpm_get(obj->tspContext, &hTpm)))
			goto done;

		offset = 0;
		Trspi_LoadBlob_BOOL(&offset, state, opData);
		opDataSize = offset;
		if ((result = do_delegate_manage(hTpm, delfamily->familyID, TPM_FAMILY_ADMIN,
				opDataSize, opData, &outDataSize, &outData)))
			goto done;
	}

	if (state)
		delfamily->stateFlags |= TSS_DELFAMILY_FLAGS_STATE_LOCKED;
	else
		delfamily->stateFlags &= ~TSS_DELFAMILY_FLAGS_STATE_LOCKED;

done:
	obj_list_put(&delfamily_list);

	free(outData);

	return result;
}
