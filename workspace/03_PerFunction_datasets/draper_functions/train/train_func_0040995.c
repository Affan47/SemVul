rdump_dirent(struct ext2_dir_entry *dirent,
			int offset EXT2FS_ATTR((unused)),
			int blocksize EXT2FS_ATTR((unused)),
			char *buf EXT2FS_ATTR((unused)), void *private)
{
	char name[EXT2_NAME_LEN + 1];
	int thislen;
	const char *dumproot = private;
	struct ext2_inode inode;

	thislen = ((dirent->name_len & 0xFF) < EXT2_NAME_LEN
		   ? (dirent->name_len & 0xFF) : EXT2_NAME_LEN);
	strncpy(name, dirent->name, thislen);
	name[thislen] = 0;

	if (debugfs_read_inode(dirent->inode, &inode, name))
		return 0;

	rdump_inode(dirent->inode, &inode, name, dumproot);

	return 0;
}
