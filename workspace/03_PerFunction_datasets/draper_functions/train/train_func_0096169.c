ext2fs_group_desc_csum_verify(ext2_filsys fs, dgrp_t group)
{
	if (EXT2_HAS_RO_COMPAT_FEATURE(fs->super,
				       EXT4_FEATURE_RO_COMPAT_GDT_CSUM) &&
	    (ext2fs_bg_checksum(fs, group) !=
	     ext2fs_group_desc_csum(fs, group)))
		return 0;

	return 1;
}
