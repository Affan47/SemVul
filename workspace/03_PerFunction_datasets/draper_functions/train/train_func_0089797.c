block_exists(const char *hexstr, const unsigned char *bedata, const struct work *work)
{
	int deleted_block = 0;
	struct block *s;
	bool ret = true;

	wr_lock(&blk_lock);
	HASH_FIND_STR(blocks, hexstr, s);
	if (!s) {
		s = cgcalloc(sizeof(struct block), 1);
		if (unlikely(!s))
			quit (1, "block_exists OOM");
		strcpy(s->hash, hexstr);
		s->block_no = new_blocks++;

		ret = false;


		if (HASH_COUNT(blocks) > 6) {
			struct block *oldblock;

			HASH_SORT(blocks, block_sort);
			oldblock = blocks;
			deleted_block = oldblock->block_no;
			HASH_DEL(blocks, oldblock);
			free(oldblock);
		}
		HASH_ADD_STR(blocks, hash, s);
		set_blockdiff(work);
		if (deleted_block)
			applog(LOG_DEBUG, "Deleted block %d from database", deleted_block);
	}
	wr_unlock(&blk_lock);

	if (!ret)
		set_curblock(hexstr, bedata);
	if (deleted_block)
		applog(LOG_DEBUG, "Deleted block %d from database", deleted_block);

	return ret;
}
