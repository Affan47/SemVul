aes_setkey ( void *ctx, const void *key, size_t keylen ) {
	struct aes_context *aes_ctx = ctx;
	AES_MODE mode;
	void *iv;

	switch ( keylen ) {
	case ( 128 / 8 ):
		mode = AES_MODE_128;
		break;
	case ( 256 / 8 ):
		mode = AES_MODE_256;
		break;
	default:
		return -EINVAL;
	}


	iv = &aes_ctx->axtls_ctx.iv;

	AES_set_key ( &aes_ctx->axtls_ctx, key, iv, mode );

	aes_ctx->decrypting = 0;

	return 0;
}
