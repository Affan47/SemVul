cm_submit_x_get_struct(struct cm_submit_x_context *ctx)
{
	int i;
	xmlrpc_value *arg;
	if (xmlrpc_value_type(ctx->results) == XMLRPC_TYPE_STRUCT) {
		return ctx->results;
	}
	if (xmlrpc_value_type(ctx->results) != XMLRPC_TYPE_ARRAY) {
		return NULL;
	}
	for (i = 0;; i++) {
		xmlrpc_array_read_item(&ctx->xenv, ctx->results, i, &arg);
		if (arg == NULL) {
			break;
		}
		if (ctx->xenv.fault_occurred) {
			xmlrpc_env_clean(&ctx->xenv);
			return NULL;
		}
		if (xmlrpc_value_type(arg) == XMLRPC_TYPE_STRUCT) {
			return arg;
		}
	}
	if (ctx->xenv.fault_occurred) {
		xmlrpc_env_clean(&ctx->xenv);
		return NULL;
	}
	return NULL;
}
