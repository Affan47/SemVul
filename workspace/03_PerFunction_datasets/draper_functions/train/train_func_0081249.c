cm_submit_x_get_s(struct cm_submit_x_context *ctx, int idx, char **s)
{
	const char *p;
	xmlrpc_value *arg;
	*s = NULL;
	if (xmlrpc_value_type(ctx->results) != XMLRPC_TYPE_ARRAY) {
		return -1;
	}
	xmlrpc_array_read_item(&ctx->xenv, ctx->results, idx, &arg);
	if (ctx->xenv.fault_occurred) {
		xmlrpc_env_clean(&ctx->xenv);
		return -1;
	} else {
		xmlrpc_read_string(&ctx->xenv, arg, &p);
		if (ctx->xenv.fault_occurred) {
			xmlrpc_env_clean(&ctx->xenv);
			return -1;
		}
		*s = talloc_strdup(ctx, p);
	}
	return 0;
}
