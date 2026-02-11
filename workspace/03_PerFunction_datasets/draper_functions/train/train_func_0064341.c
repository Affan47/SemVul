get_dirsize (void) {
	int block;
	char blk[MINIX_BLOCK_SIZE];
	size_t size;

	if (fs_version == 2)
		block = Inode2[ROOT_INO].i_zone[0];
	else
		block = Inode[ROOT_INO].i_zone[0];
	read_block (block, blk);

	for (size = 16; size < MINIX_BLOCK_SIZE; size <<= 1) {
		if (strcmp(blk + size + 2, "..") == 0) {
			dirsize = size;
			namelen = size - 2;
			return;
		}
	}

}
