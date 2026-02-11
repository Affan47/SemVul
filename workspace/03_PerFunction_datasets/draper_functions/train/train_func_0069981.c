ext2fs_iblk_set(ext2_filsys fs, struct ext2_inode *inode, blk64_t b)
{
	if (!(fs->super->s_feature_ro_compat &
	      EXT4_FEATURE_RO_COMPAT_HUGE_FILE) ||
	    !(inode->i_flags & EXT4_HUGE_FILE_FL))
		b *= fs->blocksize / 512;

	inode->i_blocks = b & 0xFFFFFFFF;
	if (fs->super->s_feature_ro_compat & EXT4_FEATURE_RO_COMPAT_HUGE_FILE)
		inode->osd2.linux2.l_i_blocks_hi = b >> 32;
	else if (b >> 32)
		return EOVERFLOW;
	return 0;
}
