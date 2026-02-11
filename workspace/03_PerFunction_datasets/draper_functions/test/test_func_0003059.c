obj_rsakey_set_size(TSS_HKEY hKey, UINT32 len)
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
	rsakey->key.pubKey.keyLength = len/8;
done:
	obj_list_put(&rsakey_list);

	return result;
}
