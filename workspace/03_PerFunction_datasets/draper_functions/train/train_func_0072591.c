completion_pages(struct work_struct *work)
{
#ifdef CONFIG_EXT4_FS_ENCRYPTION
	struct ext4_crypto_ctx *ctx =
		container_of(work, struct ext4_crypto_ctx, r.work);
	struct bio	*bio	= ctx->r.bio;
	struct bio_vec	*bv;
	int		i;

	bio_for_each_segment_all(bv, bio, i) {
		struct page *page = bv->bv_page;

		int ret = ext4_decrypt(page);
		if (ret) {
			WARN_ON_ONCE(1);
			SetPageError(page);
		} else
			SetPageUptodate(page);
		unlock_page(page);
	}
	ext4_release_crypto_ctx(ctx);
	bio_put(bio);
#else
	BUG();
#endif
}
