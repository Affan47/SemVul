ext4_release_crypto_ctx(struct ext4_crypto_ctx *ctx)
{
	unsigned long flags;

	if (ctx->flags & EXT4_WRITE_PATH_FL && ctx->w.bounce_page)
		mempool_free(ctx->w.bounce_page, ext4_bounce_page_pool);
	ctx->w.bounce_page = NULL;
	ctx->w.control_page = NULL;
	if (ctx->flags & EXT4_CTX_REQUIRES_FREE_ENCRYPT_FL) {
		kmem_cache_free(ext4_crypto_ctx_cachep, ctx);
	} else {
		spin_lock_irqsave(&ext4_crypto_ctx_lock, flags);
		list_add(&ctx->free_list, &ext4_free_crypto_ctxs);
		spin_unlock_irqrestore(&ext4_crypto_ctx_lock, flags);
	}
}
