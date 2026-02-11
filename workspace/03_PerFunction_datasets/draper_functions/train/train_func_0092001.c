sha1_final(struct sha1_ctx *ctx, u8 *out)
{
	const size_t offset = ctx->count & 0x3f;
	char *p = (char *)ctx->block + offset;
	int padding = (SHA1_BLOCK_BYTES - SHA1_COUNTER_BYTES) - (offset + 1);
	int i;

	*p++ = 0x80;

	if (padding < 0) {
		memset(p, 0, (padding + SHA1_COUNTER_BYTES));
		sha1_transform(ctx->digest, ctx->block);
		p = (char *)ctx->block;
		padding = (SHA1_BLOCK_BYTES - SHA1_COUNTER_BYTES);
	}

	memset(p, 0, padding);


	ctx->block[14] = cpu_to_be32(ctx->count >> 29);
	ctx->block[15] = cpu_to_be32(ctx->count << 3);

	sha1_transform(ctx->digest, ctx->block);

	for (i = 0; i < SHA1_DIGEST_WORDS; i++)
		ctx->digest[i] = be32_to_cpu(ctx->digest[i]);

	memcpy(out, ctx->digest, SHA1_DIGEST_BYTES);
	memset(ctx, 0, sizeof(*ctx));
}
