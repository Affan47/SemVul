use_inode_shortcuts(ext2_filsys fs, int bool)
{
	if (bool) {
		fs->get_blocks = meta_get_blocks;
		fs->check_directory = meta_check_directory;
		fs->read_inode = meta_read_inode;
		stashed_ino = 0;
	} else {
		fs->get_blocks = 0;
		fs->check_directory = 0;
		fs->read_inode = 0;
	}
}
