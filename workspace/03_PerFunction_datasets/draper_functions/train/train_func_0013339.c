prof_dump_ctx_cleanup_locked(prof_ctx_t *ctx, prof_ctx_list_t *ctx_ql)
{

	ctx->nlimbo--;
	ql_remove(ctx_ql, ctx, dump_link);
}
