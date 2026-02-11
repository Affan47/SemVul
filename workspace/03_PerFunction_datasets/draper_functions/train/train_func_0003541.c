resize_inode(ext2_filsys fs, unsigned long new_size)
{
	errcode_t retval;
	int new_ino_blks_per_grp;
	ext2fs_block_bitmap bmap;

	ext2fs_read_inode_bitmap(fs);
	ext2fs_read_block_bitmap(fs);
	INIT_LIST_HEAD(&blk_move_list);


	new_ino_blks_per_grp = ext2fs_div_ceil(
					EXT2_INODES_PER_GROUP(fs->super)*
					new_size,
					fs->blocksize);


	fs->super->s_state &= ~EXT2_VALID_FS;

	retval = ext2fs_allocate_block_bitmap(fs, _("blocks to be moved"),
						&bmap);
	if (retval) {
		fputs(_("Failed to allocate block bitmap when "
				"increasing inode size\n"), stderr);
		return retval;
	}
	retval = get_move_bitmaps(fs, new_ino_blks_per_grp, bmap);
	if (retval) {
		fputs(_("Not enough space to increase inode size \n"), stderr);
		goto err_out;
	}
	retval = move_block(fs, bmap);
	if (retval) {
		fputs(_("Failed to relocate blocks during inode resize \n"),
		      stderr);
		goto err_out;
	}
	retval = inode_scan_and_fix(fs, bmap);
	if (retval)
		goto err_out_undo;

	retval = group_desc_scan_and_fix(fs, bmap);
	if (retval)
		goto err_out_undo;

	retval = expand_inode_table(fs, new_size);
	if (retval)
		goto err_out_undo;

	ext2fs_calculate_summary_stats(fs);

	fs->super->s_state |= EXT2_VALID_FS;

	ext2fs_mark_super_dirty(fs);
	ext2fs_mark_bb_dirty(fs);

err_out:
	free_blk_move_list();
	ext2fs_free_block_bitmap(bmap);

	return retval;

err_out_undo:
	free_blk_move_list();
	ext2fs_free_block_bitmap(bmap);
	fputs(_("Error in resizing the inode size.\n"
			"Run e2undo to undo the "
			"file system changes. \n"), stderr);

	return retval;
}
