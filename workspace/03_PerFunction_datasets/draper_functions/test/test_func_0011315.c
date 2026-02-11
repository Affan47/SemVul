qrp_context_free(void *p)
{
	struct qrp_context *ctx = p;
	GSList *sl;

	g_assert(ctx->magic == QRP_MAGIC);

	qrp_dispose_words(&ctx->words);

	for (sl = ctx->sl_substrings; sl; sl = g_slist_next(sl)) {
		char *word = sl->data;
		size_t size;

		size = 1 + strlen(word);
		g_assert(size_is_positive(size));
		wfree(word, size);
	}
	gm_slist_free_null(&ctx->sl_substrings);

	HFREE_NULL(ctx->table);

	if (ctx->st)
		qrt_unref(ctx->st);
	if (ctx->lt)
		qrt_unref(ctx->lt);

	ctx->magic = 0;
	WFREE(ctx);
}
