skein_update(
	struct skein_t* ctx,
	const void* message,
	size_t message_size)
{
	size_t n;

	if (message_size + ctx->partial_count > ctx->state_bytes) {
		if (ctx->partial_count) {
			n = ctx->state_bytes - ctx->partial_count;
			if (n) {
				memcpy(ctx->partial.partial8+ctx->partial_count,
					message, n);
				message_size -= n;
				message += n;
				ctx->partial_count += n;
			}
			skein_compression(ctx, ctx->partial.partial8, 1,
				ctx->state_bytes);
			ctx->partial_count = 0;
		}
		if (message_size > ctx->state_bytes) {
			n = (message_size-1) / ctx->state_bytes;
			skein_compression(ctx, message, n, ctx->state_bytes);
			message_size -= n * ctx->state_bytes;
			message += n * ctx->state_bytes;
		}
	}
	if (message_size) {
		memcpy(ctx->partial.partial8 + ctx->partial_count,
			message, message_size);
		ctx->partial_count += message_size;
	}
}
