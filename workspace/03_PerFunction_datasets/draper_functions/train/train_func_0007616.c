sha512_end(sha512_ctx_t *ctx, void *resbuf)
{
	unsigned bufpos = ctx->total64[0] & 127;


	ctx->wbuffer[bufpos++] = 0x80;

	while (1) {
		unsigned remaining = 128 - bufpos;
		memset(ctx->wbuffer + bufpos, 0, remaining);
		if (remaining >= 16) {

			uint64_t t;
			t = ctx->total64[0] << 3;
			t = SWAP_BE64(t);
			*(uint64_t *) (&ctx->wbuffer[128 - 8]) = t;
			t = (ctx->total64[1] << 3) | (ctx->total64[0] >> 61);
			t = SWAP_BE64(t);
			*(uint64_t *) (&ctx->wbuffer[128 - 16]) = t;
		}
		sha512_process_block128(ctx);
		if (remaining >= 16)
			break;
		bufpos = 0;
	}

	if (BB_LITTLE_ENDIAN) {
		unsigned i;
		for (i = 0; i < ARRAY_SIZE(ctx->hash); ++i)
			ctx->hash[i] = SWAP_BE64(ctx->hash[i]);
	}
	memcpy(resbuf, ctx->hash, sizeof(ctx->hash));
}
