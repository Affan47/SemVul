regcache_lzo_write(struct regmap *map,
			      unsigned int reg, unsigned int value)
{
	struct regcache_lzo_ctx *lzo_block, **lzo_blocks;
	int ret, blkindex, blkpos;
	size_t blksize, tmp_dst_len;
	void *tmp_dst;


	blkindex = regcache_lzo_get_blkindex(map, reg);

	blkpos = regcache_lzo_get_blkpos(map, reg);

	blksize = regcache_lzo_get_blksize(map);
	lzo_blocks = map->cache;
	lzo_block = lzo_blocks[blkindex];


	tmp_dst = lzo_block->dst;
	tmp_dst_len = lzo_block->dst_len;


	lzo_block->src = lzo_block->dst;
	lzo_block->src_len = lzo_block->dst_len;


	ret = regcache_lzo_decompress_cache_block(map, lzo_block);
	if (ret < 0) {
		kfree(lzo_block->dst);
		goto out;
	}


	if (regcache_set_val(map, lzo_block->dst, blkpos, value)) {
		kfree(lzo_block->dst);
		goto out;
	}


	lzo_block->src = lzo_block->dst;
	lzo_block->src_len = lzo_block->dst_len;


	ret = regcache_lzo_compress_cache_block(map, lzo_block);
	if (ret < 0) {
		kfree(lzo_block->dst);
		kfree(lzo_block->src);
		goto out;
	}


	set_bit(reg / map->reg_stride, lzo_block->sync_bmp);
	kfree(tmp_dst);
	kfree(lzo_block->src);
	return 0;
out:
	lzo_block->dst = tmp_dst;
	lzo_block->dst_len = tmp_dst_len;
	return ret;
}
