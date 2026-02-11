obj_tpm_set_cred(TSS_HTPM hTpm, TSS_FLAG type, UINT32 CredSize, BYTE *CredData)
{
	struct tsp_object *obj;
	struct tr_tpm_obj *tpm;
	TSS_RESULT result = TSS_SUCCESS;

	if ((obj = obj_list_get_obj(&tpm_list, hTpm)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	tpm = (struct tr_tpm_obj *)obj->data;

	switch (type) {
		case TSS_TPMATTRIB_EKCERT:
			if ((tpm->EndorsementCred = malloc(CredSize)) == NULL) {
				LogError("malloc of %u bytes failed", CredSize);
				result = TSPERR(TSS_E_OUTOFMEMORY);
				goto done;
			}
			memcpy(tpm->EndorsementCred, CredData, CredSize);
			tpm->EndorsementCredSize = CredSize;
			break;
		case TSS_TPMATTRIB_TPM_CC:
			if ((tpm->ConformanceCred = malloc(CredSize)) == NULL) {
				LogError("malloc of %u bytes failed", CredSize);
				result = TSPERR(TSS_E_OUTOFMEMORY);
				goto done;
			}
			memcpy(tpm->ConformanceCred, CredData, CredSize);
			tpm->ConformanceCredSize = CredSize;
			break;
		case TSS_TPMATTRIB_PLATFORMCERT:
			if ((tpm->PlatformCred = malloc(CredSize)) == NULL) {
				LogError("malloc of %u bytes failed", CredSize);
				result = TSPERR(TSS_E_OUTOFMEMORY);
				goto done;
			}
			memcpy(tpm->PlatformCred, CredData, CredSize);
			tpm->PlatformCredSize = CredSize;
			break;
		case TSS_TPMATTRIB_PLATFORM_CC:
			if ((tpm->PlatformConfCred = malloc(CredSize)) == NULL) {
				LogError("malloc of %u bytes failed", CredSize);
				result = TSPERR(TSS_E_OUTOFMEMORY);
				goto done;
			}
			memcpy(tpm->PlatformConfCred, CredData, CredSize);
			tpm->PlatformConfCredSize = CredSize;
			break;
		default:
			result = TSPERR(TSS_E_INVALID_ATTRIB_FLAG);
			break;
	}
done:
	obj_list_put(&tpm_list);

	return result;
}
