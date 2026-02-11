obj_tpm_get_cred(TSS_HTPM hTpm, TSS_FLAG type, UINT32 *CredSize, BYTE **CredData)
{
	struct tsp_object *obj;
	struct tr_tpm_obj *tpm;
	TSS_RESULT result = TSS_SUCCESS;

	if ((obj = obj_list_get_obj(&tpm_list, hTpm)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	tpm = (struct tr_tpm_obj *)obj->data;


	switch (type) {
		case TSS_TPMATTRIB_EKCERT:
			*CredSize = tpm->EndorsementCredSize;
			break;
		case TSS_TPMATTRIB_TPM_CC:
			*CredSize = tpm->ConformanceCredSize;
			break;
		case TSS_TPMATTRIB_PLATFORMCERT:
			*CredSize = tpm->PlatformCredSize;
			break;
		case TSS_TPMATTRIB_PLATFORM_CC:
			*CredSize = tpm->PlatformConfCredSize;
			break;
		default:
			LogError("Credential type is unknown");
			result = TSPERR(TSS_E_INTERNAL_ERROR);
			goto done;
	}

	if (*CredSize == 0) {
		*CredData = NULL;
		goto done;
	}

	if ((*CredData = calloc_tspi(obj->tspContext, *CredSize)) == NULL) {
		*CredSize = 0;
		result = TSPERR(TSS_E_OUTOFMEMORY);
		goto done;
	}

	switch (type) {
		case TSS_TPMATTRIB_EKCERT:
			memcpy(*CredData, tpm->EndorsementCred, *CredSize);
			break;
		case TSS_TPMATTRIB_TPM_CC:
			memcpy(*CredData, tpm->ConformanceCred, *CredSize);
			break;
		case TSS_TPMATTRIB_PLATFORMCERT:
			memcpy(*CredData, tpm->PlatformCred, *CredSize);
			break;
		case TSS_TPMATTRIB_PLATFORM_CC:
			memcpy(*CredData, tpm->PlatformConfCred, *CredSize);
			break;
		default:
			result = TSPERR(TSS_E_BAD_PARAMETER);
			*CredSize = 0;
			free(*CredData);
			*CredData = NULL;
			break;
	}

done:
	obj_list_put(&tpm_list);
	return result;
}
