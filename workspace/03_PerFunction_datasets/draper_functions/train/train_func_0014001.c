f2fs_crypto_destroy(void)
{
	struct f2fs_crypto_ctx *pos, *n;

	list_for_each_entry_safe(pos, n, &f2fs_free_crypto_ctxs, free_list)
		kmem_cache_free(f2fs_crypto_ctx_cachep, pos);
	INIT_LIST_HEAD(&f2fs_free_crypto_ctxs);
	if (f2fs_bounce_page_pool)
		mempool_destroy(f2fs_bounce_page_pool);
	f2fs_bounce_page_pool = NULL;
}
