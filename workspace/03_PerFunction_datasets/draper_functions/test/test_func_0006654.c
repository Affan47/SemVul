__glue_xts_crypt_128bit(const struct common_glue_ctx *gctx,
					    void *ctx,
					    struct blkcipher_desc *desc,
					    struct blkcipher_walk *walk)
{
	const unsigned int bsize = 128 / 8;
	unsigned int nbytes = walk->nbytes;
	u128 *src = (u128 *)walk->src.virt.addr;
	u128 *dst = (u128 *)walk->dst.virt.addr;
	unsigned int num_blocks, func_bytes;
	unsigned int i;


	for (i = 0; i < gctx->num_funcs; i++) {
		num_blocks = gctx->funcs[i].num_blocks;
		func_bytes = bsize * num_blocks;

		if (nbytes >= func_bytes) {
			do {
				gctx->funcs[i].fn_u.xts(ctx, dst, src,
							(le128 *)walk->iv);

				src += num_blocks;
				dst += num_blocks;
				nbytes -= func_bytes;
			} while (nbytes >= func_bytes);

			if (nbytes < bsize)
				goto done;
		}
	}

done:
	return nbytes;
}
