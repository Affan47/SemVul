ext2fs_group_desc_csum_set(ext2_filsys fs, dgrp_t group)
{
	if (!EXT2_HAS_RO_COMPAT_FEATURE(fs->super,
					EXT4_FEATURE_RO_COMPAT_GDT_CSUM))
		return;


	ext2fs_bg_checksum_set(fs, group, ext2fs_group_desc_csum(fs, group));
}
