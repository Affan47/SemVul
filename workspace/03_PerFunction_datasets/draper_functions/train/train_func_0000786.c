bt_store_piece_sha1(torrent_ctx *ctx)
{
	unsigned char* block;
	unsigned char* hash;

	if((ctx->piece_count % BT_BLOCK_SIZE) == 0) {
		block = (unsigned char*)malloc(BT_HASH_SIZE * BT_BLOCK_SIZE);
		if(block == NULL || !bt_vector_add_ptr(&ctx->hash_blocks, block)) {
			if(block) free(block);
			return 0;
		}
	} else {
		block = (unsigned char*)(ctx->hash_blocks.array[ctx->piece_count / BT_BLOCK_SIZE]);
	}

	hash = &block[BT_HASH_SIZE * (ctx->piece_count % BT_BLOCK_SIZE)];
	SHA1_FINAL(ctx, hash);
	ctx->piece_count++;
	return 1;
}
