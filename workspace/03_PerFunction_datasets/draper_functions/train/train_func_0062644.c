block_group_used(struct super_block *s, u32 id)
{
	int bm = bmap_hash_id(s, id);
	struct reiserfs_bitmap_info *info = &SB_AP_BITMAP(s)[bm];


	if (info->free_count == UINT_MAX) {
		struct buffer_head *bh = reiserfs_read_bitmap_block(s, bm);
		brelse(bh);
	}

	if (info->free_count > ((s->s_blocksize << 3) * 60 / 100)) {
		return 0;
	}
	return 1;
}
