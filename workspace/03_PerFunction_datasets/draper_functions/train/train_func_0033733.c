obj_policy_get_counter(TSS_HPOLICY hPolicy, UINT32 *counter)
{
	struct tsp_object *obj;
	struct tr_policy_obj *policy;
	TSS_RESULT result = TSS_SUCCESS;

	if ((obj = obj_list_get_obj(&policy_list, hPolicy)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	policy = (struct tr_policy_obj *)obj->data;

	if (policy->SecretLifetime == TSS_TSPATTRIB_POLICYSECRET_LIFETIME_COUNTER)
		*counter = policy->SecretCounter;
	else
		result = TSPERR(TSS_E_INVALID_OBJ_ACCESS);

	obj_list_put(&policy_list);

	return result;
}
