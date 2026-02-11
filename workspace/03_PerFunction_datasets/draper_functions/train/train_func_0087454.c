rhash_whirlpool_final(whirlpool_ctx *ctx, unsigned char* result)
{
	unsigned index = (unsigned)ctx->length & 63;
	uint64_t* msg64 = (uint64_t*)ctx->message;


	ctx->message[index++] = 0x80;


	if(index > 32) {

		while(index < 64) {
			ctx->message[index++] = 0;
		}
		rhash_whirlpool_process_block(ctx->hash, msg64);
		index = 0;
	}

	while(index < 56) {
		ctx->message[index++] = 0;
	}
	msg64[7] = be2me_64(ctx->length << 3);
	rhash_whirlpool_process_block(ctx->hash, msg64);


	be64_copy(result, 0, ctx->hash, 64);
}
