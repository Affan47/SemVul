rhash_sha256_final(sha256_ctx *ctx, unsigned char* result)
{
	size_t index = ((unsigned)ctx->length & 63) >> 2;
	unsigned shift = ((unsigned)ctx->length & 3) * 8;


	ctx->message[index]   &= le2me_32(~(0xFFFFFFFF << shift));
	ctx->message[index++] ^= le2me_32(0x80 << shift);


	if(index > 14) {

		while(index < 16) {
			ctx->message[index++] = 0;
		}
		rhash_sha256_process_block(ctx->hash, ctx->message);
		index = 0;
	}
	while(index < 14) {
		ctx->message[index++] = 0;
	}
	ctx->message[14] = be2me_32( (unsigned)(ctx->length >> 29) );
	ctx->message[15] = be2me_32( (unsigned)(ctx->length << 3) );
	rhash_sha256_process_block(ctx->hash, ctx->message);

	if(result) be32_copy(result, 0, ctx->hash, ctx->digest_length);
}
