ext2fs_calculate_summary_stats(ext2_filsys fs)
{
	blk_t		blk;
	ext2_ino_t	ino;
	unsigned int	group = 0;
	unsigned int	count = 0;
	int		total_free = 0;
	int		group_free = 0;


	for (blk = fs->super->s_first_data_block;
	     blk < fs->super->s_blocks_count; blk++) {
		if (!ext2fs_fast_test_block_bitmap(fs->block_map, blk)) {
			group_free++;
			total_free++;
		}
		count++;
		if ((count == fs->super->s_blocks_per_group) ||
		    (blk == fs->super->s_blocks_count-1)) {
			fs->group_desc[group++].bg_free_blocks_count =
				group_free;
			count = 0;
			group_free = 0;
		}
	}
	fs->super->s_free_blocks_count = total_free;


	group_free = 0;
	total_free = 0;
	count = 0;
	group = 0;


	for (ino = 1; ino <= fs->super->s_inodes_count && ino > 0; ino++) {
		if (!ext2fs_fast_test_inode_bitmap(fs->inode_map, ino)) {
			group_free++;
			total_free++;
		}
		count++;
		if ((count == fs->super->s_inodes_per_group) ||
		    (ino == fs->super->s_inodes_count)) {
			fs->group_desc[group++].bg_free_inodes_count =
				group_free;
			count = 0;
			group_free = 0;
		}
	}
	fs->super->s_free_inodes_count = total_free;
	ext2fs_mark_super_dirty(fs);
	return 0;
}
