triton_context_print(void)
{
	struct _triton_context_t *ctx;

	list_for_each_entry(ctx, &ctx_list, entry)
		printf("%p\n", ctx);
}
