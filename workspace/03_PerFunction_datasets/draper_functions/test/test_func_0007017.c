MD5_Final(unsigned char *result, MD5_CTX *ctx)
{
	unsigned long used, free;

	used = ctx->lo & 0x3f;

	ctx->buffer[used++] = 0x80;

	free = 64 - used;

	if (free < 8) {
		memset(&ctx->buffer[used], 0, free);
		md5_body(ctx, ctx->buffer, 64);
		used = 0;
		free = 64;
	}

	memset(&ctx->buffer[used], 0, free - 8);

	ctx->lo <<= 3;
	ctx->buffer[56] = ctx->lo;
	ctx->buffer[57] = ctx->lo >> 8;
	ctx->buffer[58] = ctx->lo >> 16;
	ctx->buffer[59] = ctx->lo >> 24;
	ctx->buffer[60] = ctx->hi;
	ctx->buffer[61] = ctx->hi >> 8;
	ctx->buffer[62] = ctx->hi >> 16;
	ctx->buffer[63] = ctx->hi >> 24;

	md5_body(ctx, ctx->buffer, 64);

	result[0] = ctx->a;
	result[1] = ctx->a >> 8;
	result[2] = ctx->a >> 16;
	result[3] = ctx->a >> 24;
	result[4] = ctx->b;
	result[5] = ctx->b >> 8;
	result[6] = ctx->b >> 16;
	result[7] = ctx->b >> 24;
	result[8] = ctx->c;
	result[9] = ctx->c >> 8;
	result[10] = ctx->c >> 16;
	result[11] = ctx->c >> 24;
	result[12] = ctx->d;
	result[13] = ctx->d >> 8;
	result[14] = ctx->d >> 16;
	result[15] = ctx->d >> 24;

	memset(ctx, 0, sizeof(*ctx));
}
