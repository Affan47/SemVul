obj_rsakey_set_alg(TSS_HKEY hKey, UINT32 alg)
{
	struct tsp_object *obj;
	struct tr_rsakey_obj *rsakey;
	TSS_RESULT result = TSS_SUCCESS;

	if ((obj = obj_list_get_obj(&rsakey_list, hKey)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	if (obj->flags & TSS_OBJ_FLAG_KEY_SET) {
		result = TSPERR(TSS_E_INVALID_OBJ_ACCESS);
		goto done;
	}

	rsakey = (struct tr_rsakey_obj *)obj->data;
	switch (alg) {
		case TSS_ALG_RSA:
			rsakey->key.algorithmParms.algorithmID = TCPA_ALG_RSA;
			break;
		default:
			rsakey->key.algorithmParms.algorithmID = alg;
			break;
	}
done:
	obj_list_put(&rsakey_list);

	return result;
}
