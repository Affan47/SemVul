obj_context_get_connection_version(TSS_HCONTEXT tspContext, UINT32 *version)
{
	struct tsp_object *obj;
	struct tr_context_obj *context;

	if ((obj = obj_list_get_obj(&context_list, tspContext)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	context = (struct tr_context_obj *)obj->data;

	*version = context->current_connection;

	obj_list_put(&context_list);

	return TSS_SUCCESS;
}
