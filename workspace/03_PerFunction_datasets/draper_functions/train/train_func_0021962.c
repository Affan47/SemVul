obj_tpm_set_cb12(TSS_HTPM hTpm, TSS_FLAG flag, BYTE *in)
{
	struct tsp_object *obj;
	struct tr_tpm_obj *tpm;
	TSS_RESULT result = TSS_SUCCESS;
	TSS_CALLBACK *cb = (TSS_CALLBACK *)in;

	if ((obj = obj_list_get_obj(&tpm_list, hTpm)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	tpm = (struct tr_tpm_obj *)obj->data;

	switch (flag) {
		case TSS_TSPATTRIB_TPM_CALLBACK_COLLATEIDENTITY:
			if (!cb) {
				tpm->Tspicb_CollateIdentity = NULL;
				break;
			}

			tpm->Tspicb_CollateIdentity = (TSS_RESULT (*)(PVOID,
				UINT32, BYTE *, TSS_ALGORITHM_ID, UINT32 *,
				BYTE *, UINT32 *, BYTE *))cb->callback;
			tpm->collateAppData = cb->appData;
			tpm->collateAlg = cb->alg;
			break;
		case TSS_TSPATTRIB_TPM_CALLBACK_ACTIVATEIDENTITY:
			if (!cb) {
				tpm->Tspicb_ActivateIdentity = NULL;
				break;
			}

			tpm->Tspicb_ActivateIdentity = (TSS_RESULT (*)(PVOID,
				UINT32, BYTE *, UINT32, BYTE *, UINT32 *,
				BYTE *))cb->callback;
			tpm->activateAppData = cb->appData;
			tpm->activateAlg = cb->alg;
			break;
		default:
			result = TSPERR(TSS_E_INVALID_ATTRIB_FLAG);
			break;
	}

	obj_list_put(&tpm_list);

	return result;
}
