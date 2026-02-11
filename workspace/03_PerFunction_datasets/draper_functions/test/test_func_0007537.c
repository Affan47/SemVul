inode_attach_direct_blocks(struct ext4_inode *inode,
		struct block_allocation *alloc, u32 *block_len)
{
	int len = min(*block_len, EXT4_NDIR_BLOCKS);
	int i;

	for (i = 0; i < len; i++) {
		inode->i_block[i] = get_block(alloc, i);
	}

	if (advance_blocks(alloc, len)) {
		error("failed to advance %d blocks", len);
		return -1;
	}

	*block_len -= len;
	return 0;
}
