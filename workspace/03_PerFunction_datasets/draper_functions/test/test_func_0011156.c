group_desc_scan_and_fix(ext2_filsys fs, ext2fs_block_bitmap bmap)
{
	dgrp_t i;
	blk_t blk, new_blk;

	for (i = 0; i < fs->group_desc_count; i++) {
		blk = fs->group_desc[i].bg_block_bitmap;
		if (ext2fs_test_block_bitmap(bmap, blk)) {
			new_blk = translate_block(blk);
			if (!new_blk)
				continue;
			fs->group_desc[i].bg_block_bitmap = new_blk;
		}

		blk = fs->group_desc[i].bg_inode_bitmap;
		if (ext2fs_test_block_bitmap(bmap, blk)) {
			new_blk = translate_block(blk);
			if (!new_blk)
				continue;
			fs->group_desc[i].bg_inode_bitmap = new_blk;
		}
	}
	return 0;
}
