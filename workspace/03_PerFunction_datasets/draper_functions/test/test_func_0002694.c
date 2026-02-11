html_context_free(struct html_context **ctx_ptr)
{
	struct html_context *ctx = *ctx_ptr;
	if (ctx) {
		str_destroy_null(&ctx->title);
		html_output_free(&ctx->output);
		WFREE(ctx);
		*ctx_ptr = NULL;
	}
}
