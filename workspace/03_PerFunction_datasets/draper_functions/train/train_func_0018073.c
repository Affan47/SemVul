obj_policy_get_delegation_index(TSS_HPOLICY hPolicy, UINT32 *index)
{
	struct tsp_object *obj;
	struct tr_policy_obj *policy;
	TSS_RESULT result = TSS_SUCCESS;

	if ((obj = obj_list_get_obj(&policy_list, hPolicy)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	policy = (struct tr_policy_obj *)obj->data;

	if (!policy->delegationIndexSet) {
		result = TSPERR(TSS_E_INVALID_OBJ_ACCESS);
		goto done;
	}

	*index = policy->delegationIndex;

done:
	obj_list_put(&policy_list);

	return result;
}
