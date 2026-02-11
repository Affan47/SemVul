obj_policy_get_delegation_pcr_selection(TSS_HPOLICY hPolicy, UINT32 *selectionLength,
					BYTE **selection)
{
	struct tsp_object *obj;
	struct tr_policy_obj *policy;
	TPM_DELEGATE_PUBLIC public;
	UINT64 offset;
	TSS_RESULT result = TSS_SUCCESS;

	if ((obj = obj_list_get_obj(&policy_list, hPolicy)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	policy = (struct tr_policy_obj *)obj->data;

	if (policy->delegationIndexSet || policy->delegationBlob) {
		if ((result = obj_policy_get_delegate_public(obj, &public)))
			goto done;
		offset = 0;
		Trspi_LoadBlob_PCR_SELECTION(&offset, NULL, &public.pcrInfo.pcrSelection);
		*selection = calloc_tspi(obj->tspContext, offset);
		if (*selection == NULL) {
			LogError("malloc of %u bytes failed.", (UINT32)offset);
			result = TSPERR(TSS_E_OUTOFMEMORY);
			goto done;
		}
		offset = 0;
		Trspi_LoadBlob_PCR_SELECTION(&offset, *selection, &public.pcrInfo.pcrSelection);
		*selectionLength = offset;
		free(public.pcrInfo.pcrSelection.pcrSelect);
	} else
		result = TSPERR(TSS_E_INVALID_OBJ_ACCESS);

done:
	obj_list_put(&policy_list);

	return result;
}
