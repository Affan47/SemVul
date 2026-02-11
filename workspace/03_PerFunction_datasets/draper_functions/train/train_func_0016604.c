ext4_encrypt(struct inode *inode,
			  struct page *plaintext_page,
			  gfp_t gfp_flags)
{
	struct ext4_crypto_ctx *ctx;
	struct page *ciphertext_page = NULL;
	int err;

	BUG_ON(!PageLocked(plaintext_page));

	ctx = ext4_get_crypto_ctx(inode, gfp_flags);
	if (IS_ERR(ctx))
		return (struct page *) ctx;


	ciphertext_page = alloc_bounce_page(ctx, gfp_flags);
	if (IS_ERR(ciphertext_page))
		goto errout;
	ctx->w.control_page = plaintext_page;
	err = ext4_page_crypto(inode, EXT4_ENCRYPT, plaintext_page->index,
			       plaintext_page, ciphertext_page, gfp_flags);
	if (err) {
		ciphertext_page = ERR_PTR(err);
	errout:
		ext4_release_crypto_ctx(ctx);
		return ciphertext_page;
	}
	SetPagePrivate(ciphertext_page);
	set_page_private(ciphertext_page, (unsigned long)ctx);
	lock_page(ciphertext_page);
	return ciphertext_page;
}
