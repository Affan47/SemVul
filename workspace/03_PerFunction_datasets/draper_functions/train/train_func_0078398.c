obj_context_get_machine_name(TSS_HCONTEXT tspContext, UINT32 *size, BYTE **data)
{
	struct tsp_object *obj;
	struct tr_context_obj *context;
	TSS_RESULT result;

	if ((obj = obj_list_get_obj(&context_list, tspContext)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	context = (struct tr_context_obj *)obj->data;

	if (context->machineNameLength == 0) {
		*data = NULL;
		*size = 0;
	} else {


		*data = calloc(1, context->machineNameLength);
		if (*data == NULL) {
			LogError("malloc of %u bytes failed.",
					context->machineNameLength);
			result = TSPERR(TSS_E_OUTOFMEMORY);
			goto done;
		}
		*size = context->machineNameLength;
		memcpy(*data, context->machineName, *size);
	}

	result = TSS_SUCCESS;

done:
	obj_list_put(&context_list);

	return result;
}
