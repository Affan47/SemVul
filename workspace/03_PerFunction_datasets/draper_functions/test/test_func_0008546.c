MD5_Update(MD5_CTX *ctx, void *data, unsigned long size)
{
	MD5_u32plus saved_lo;
	unsigned long used, free;

	saved_lo = ctx->lo;
	if ((ctx->lo = (saved_lo + size) & 0x1fffffff) < saved_lo)
		ctx->hi++;
	ctx->hi += size >> 29;

	used = saved_lo & 0x3f;

	if (used) {
		free = 64 - used;

		if (size < free) {
			egg_memcpy(&ctx->buffer[used], data, size);
			return;
		}

		egg_memcpy(&ctx->buffer[used], data, free);
		data = ((unsigned char *)data) + free;
		size -= free;
		body(ctx, ctx->buffer, 64);
	}

	if (size >= 64) {
		data = body(ctx, data, size & ~(unsigned long)0x3f);
		size &= 0x3f;
	}

	egg_memcpy(ctx->buffer, data, size);
}
