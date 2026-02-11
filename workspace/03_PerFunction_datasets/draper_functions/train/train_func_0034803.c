thex_download_create(void *owner, gnet_host_t *host,
	const struct sha1 *sha1, const struct tth *tth, filesize_t filesize)
{
	static const struct thex_download zero_ctx;
	struct thex_download *ctx;

	g_return_val_if_fail(host, NULL);
	g_return_val_if_fail(sha1, NULL);
	g_return_val_if_fail(tth, NULL);

	WALLOC(ctx);
	*ctx = zero_ctx;
	ctx->owner = owner;
	gnet_host_copy(&ctx->host, host);
	ctx->sha1 = atom_sha1_get(sha1);
	ctx->tth = atom_tth_get(tth);
	ctx->filesize = filesize;

	return ctx;
}
