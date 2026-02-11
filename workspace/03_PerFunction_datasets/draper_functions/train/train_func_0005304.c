opt_remove(struct bouquet_ctx *ctx, int argc, char **argv)
{
	struct bouquet *bp;
	int i;

	HTABLE_FOREACH(&ctx->bouquets, bp, struct bouquet, hash,
		for (i = 1; i < argc; i++) {
			if (pattern_match(argv[i], bp->bouquet_name) == 0) {
				htable_remove_noresize(&ctx->bouquets, &bp->hash);
				bouquet_entry_free(bp);
			}
		}
	);
}
