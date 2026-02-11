rhash_sha3_update(sha3_ctx *ctx, const unsigned char *msg, size_t size)
{
	size_t index = (size_t)ctx->rest;
	size_t block_size = (size_t)ctx->block_size;

	if (ctx->rest & SHA3_FINALIZED) return;
	ctx->rest = (unsigned)((ctx->rest + size) % block_size);


	if (index) {
		size_t left = block_size - index;
		memcpy((char*)ctx->message + index, msg, (size < left ? size : left));
		if (size < left) return;


		rhash_sha3_process_block(ctx->hash, ctx->message, block_size);
		msg  += left;
		size -= left;
	}
	while (size >= block_size) {
		uint64_t* aligned_message_block;
		if (IS_ALIGNED_64(msg)) {


			aligned_message_block = (uint64_t*)msg;
		} else {
			memcpy(ctx->message, msg, block_size);
			aligned_message_block = ctx->message;
		}

		rhash_sha3_process_block(ctx->hash, aligned_message_block, block_size);
		msg  += block_size;
		size -= block_size;
	}
	if (size) {
		memcpy(ctx->message, msg, size);
	}
}
