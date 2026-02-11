ext2fs_get_num_dirs(ext2_filsys fs, ext2_ino_t *ret_num_dirs)
{
	dgrp_t	i;
	ext2_ino_t	num_dirs, max_dirs;

	EXT2_CHECK_MAGIC(fs, EXT2_ET_MAGIC_EXT2FS_FILSYS);

	num_dirs = 0;
	max_dirs = fs->super->s_inodes_per_group;
	for (i = 0; i < fs->group_desc_count; i++) {
		if (fs->group_desc[i].bg_used_dirs_count > max_dirs)
			num_dirs += max_dirs / 8;
		else
			num_dirs += fs->group_desc[i].bg_used_dirs_count;
	}
	if (num_dirs > fs->super->s_inodes_count)
		num_dirs = fs->super->s_inodes_count;

	*ret_num_dirs = num_dirs;

	return 0;
}
