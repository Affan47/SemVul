ext2fs_allocate_tables(ext2_filsys fs)
{
	errcode_t	retval;
	dgrp_t		i;
	struct ext2fs_numeric_progress_struct progress;

	ext2fs_numeric_progress_init(fs, &progress, NULL,
				     fs->group_desc_count);

	for (i = 0; i < fs->group_desc_count; i++) {
		ext2fs_numeric_progress_update(fs, &progress, i);
		retval = ext2fs_allocate_group_table(fs, i, fs->block_map);
		if (retval)
			return retval;
	}
	ext2fs_numeric_progress_close(fs, &progress, NULL);
	return 0;
}
