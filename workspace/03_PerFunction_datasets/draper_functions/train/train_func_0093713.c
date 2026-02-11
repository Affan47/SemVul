clear_block_uninit(ext2_filsys fs, dgrp_t group)
{
	if (!(EXT2_HAS_RO_COMPAT_FEATURE(fs->super,
					 EXT4_FEATURE_RO_COMPAT_GDT_CSUM)) ||
	    !(ext2fs_bg_flags_test(fs, group, EXT2_BG_BLOCK_UNINIT)))
		return;


	ext2fs_bg_flags_clear(fs, group, EXT2_BG_BLOCK_UNINIT);
	ext2fs_group_desc_csum_set(fs, group);
	ext2fs_mark_super_dirty(fs);
	ext2fs_mark_bb_dirty(fs);
}
