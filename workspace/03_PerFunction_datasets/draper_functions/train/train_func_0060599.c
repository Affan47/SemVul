common64_hash(md5_ctx_t *ctx, const void *buffer, size_t len)
{
	unsigned bufpos = ctx->total64 & 63;

	ctx->total64 += len;

	while (1) {
		unsigned remaining = 64 - bufpos;
		if (remaining > len)
			remaining = len;

		memcpy(ctx->wbuffer + bufpos, buffer, remaining);
		len -= remaining;
		buffer = (const char *)buffer + remaining;
		bufpos += remaining;

		bufpos -= 64;
		if (bufpos != 0)
			break;

		ctx->process_block(ctx);

	}
}
