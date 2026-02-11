obj_rsakey_set_policy(TSS_HKEY hKey, TSS_HPOLICY hPolicy)
{
	struct tsp_object *obj;
	struct tr_rsakey_obj *rsakey;
	UINT32 policyType;
	TSS_RESULT result = TSS_SUCCESS;

	if ((result = obj_policy_get_type(hPolicy, &policyType)))
		return result;

	if ((obj = obj_list_get_obj(&rsakey_list, hKey)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	rsakey = (struct tr_rsakey_obj *)obj->data;

	switch (policyType) {
		case TSS_POLICY_USAGE:
			rsakey->usagePolicy = hPolicy;
			break;
		case TSS_POLICY_MIGRATION:
			rsakey->migPolicy = hPolicy;
			break;
		default:
			result = TSPERR(TSS_E_BAD_PARAMETER);
	}

	obj_list_put(&rsakey_list);

	return result;
}
