alloc_inlining_context(struct vm_method *method)
{
	struct inlining_context *ctx;
	int size;

	ctx = malloc(sizeof(*ctx));
	if (!ctx)
		return NULL;

	ctx->method = method;

	INIT_LIST_HEAD(&ctx->subroutine_list);

	ctx->subroutines = alloc_hash_map(&sub_lookup_ops);
	if (!ctx->subroutines)
		goto error_code;

	if (code_state_init(&ctx->code, method->code_attribute.code,
			    method->code_attribute.code_length))
		goto error_code;

	ctx->exception_table_length =
		method->code_attribute.exception_table_length;
	size = sizeof(*method->code_attribute.exception_table) *
		ctx->exception_table_length;
	ctx->exception_table = malloc(size);
	if (!ctx->exception_table)
		goto error_exception_table;

	memcpy(ctx->exception_table, method->code_attribute.exception_table,
	       size);


	if (pc_map_init_identity(&ctx->pc_map, ctx->code.code_length + 1))
		goto error_pc_map;

	return ctx;

 error_pc_map:
	free(ctx->exception_table);
 error_exception_table:
	free(ctx->code.code);
 error_code:
	free(ctx);

	return NULL;
}
