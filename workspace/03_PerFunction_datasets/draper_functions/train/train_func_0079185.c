get_new_block(ext2_resize_t rfs)
{
	ext2_filsys	fs = rfs->new_fs;

	while (1) {
		if (rfs->new_blk >= fs->super->s_blocks_count) {
			if (rfs->alloc_state == DESPERATION)
				return 0;

#ifdef RESIZE2FS_DEBUG
			if (rfs->flags & RESIZE_DEBUG_BMOVE)
				printf("Going into desperation mode "
				       "for block allocations\n");
#endif
			rfs->alloc_state = DESPERATION;
			rfs->new_blk = fs->super->s_first_data_block;
			continue;
		}
		if (ext2fs_test_block_bitmap(fs->block_map, rfs->new_blk) ||
		    ext2fs_test_block_bitmap(rfs->reserve_blocks,
					     rfs->new_blk) ||
		    ((rfs->alloc_state == AVOID_OLD) &&
		     (rfs->new_blk < rfs->old_fs->super->s_blocks_count) &&
		     ext2fs_test_block_bitmap(rfs->old_fs->block_map,
					      rfs->new_blk))) {
			rfs->new_blk++;
			continue;
		}
		return rfs->new_blk;
	}
}
