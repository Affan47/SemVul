ext2fs_group_last_block2(ext2_filsys fs, dgrp_t group)
{
	return (group == fs->group_desc_count - 1 ?
		ext2fs_blocks_count(fs->super) - 1 :
		ext2fs_group_first_block2(fs, group) +
			(fs->super->s_blocks_per_group - 1));
}
