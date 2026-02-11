vmw_binding_drop(struct vmw_ctx_bindinfo *bi)
{
	list_del(&bi->ctx_list);
	if (!list_empty(&bi->res_list))
		list_del(&bi->res_list);
	bi->ctx = NULL;
}
