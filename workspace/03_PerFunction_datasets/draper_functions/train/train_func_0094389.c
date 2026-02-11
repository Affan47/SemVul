ext4_dirent_csum_verify(struct inode *inode, struct ext4_dir_entry *dirent)
{
	struct ext4_dir_entry_tail *t;

	if (!ext4_has_metadata_csum(inode->i_sb))
		return 1;

	t = get_dirent_tail(inode, dirent);
	if (!t) {
		warn_no_space_for_csum(inode);
		return 0;
	}

	if (t->det_checksum != ext4_dirent_csum(inode, dirent,
						(void *)t - (void *)dirent))
		return 0;

	return 1;
}
