Tspi_ChangeAuth(TSS_HOBJECT hObjectToChange,
		TSS_HOBJECT hParentObject,
		TSS_HPOLICY hNewPolicy)
{
	UINT32 keyToChangeHandle;
	TSS_RESULT result;
	TSS_HCONTEXT tspContext;

	if ((result = obj_policy_get_tsp_context(hNewPolicy, &tspContext)))
		return result;


	if (obj_is_tpm(hObjectToChange)) {
		if (hParentObject != NULL_HOBJECT)
			return TSPERR(TSS_E_BAD_PARAMETER);
	} else if (!obj_is_rsakey(hParentObject) && !obj_is_tpm(hParentObject)) {
		return TSPERR(TSS_E_INVALID_HANDLE);
	}

	if (obj_is_tpm(hObjectToChange)) {
		if ((result = changeauth_owner(tspContext, hObjectToChange, NULL_HTPM, hNewPolicy)))
			return result;
	} else if (obj_is_rsakey(hObjectToChange)) {
		if ((result = obj_rsakey_get_tcs_handle(hObjectToChange, &keyToChangeHandle)))
			return result;

		if (keyToChangeHandle == TPM_KEYHND_SRK) {
			if ((result = changeauth_srk(tspContext, hObjectToChange, hParentObject,
						     hNewPolicy)))
				return result;
		} else {
			if ((result = changeauth_key(tspContext, hObjectToChange, hParentObject,
						     hNewPolicy)))
				return result;
		}
	} else if (obj_is_encdata(hObjectToChange)) {
		if ((result = changeauth_encdata(tspContext, hObjectToChange, hParentObject,
						 hNewPolicy)))
			return result;
	} else if (obj_is_policy(hObjectToChange) || obj_is_hash(hObjectToChange) ||
		   obj_is_pcrs(hObjectToChange) || obj_is_context(hObjectToChange)) {
		return TSPERR(TSS_E_BAD_PARAMETER);
	} else {
		return TSPERR(TSS_E_INVALID_HANDLE);
	}

	if ((result = obj_policy_set_type(hNewPolicy, TSS_POLICY_USAGE)))
		return result;

	return Tspi_Policy_AssignToObject(hNewPolicy, hObjectToChange);

}
