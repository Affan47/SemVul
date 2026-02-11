inode_allocate_indirect(struct ext4_inode *inode, unsigned long len)
{
	struct block_allocation *alloc;
	u32 block_len = DIV_ROUND_UP(len, info.block_size);
	u32 indirect_len = indirect_blocks_needed(block_len);

	alloc = do_inode_allocate_indirect(inode, block_len);
	if (alloc == NULL) {
		error("failed to allocate extents for %lu bytes", len);
		return;
	}

	reserve_all_indirect_blocks(alloc, block_len);
	rewind_alloc(alloc);

	if (do_inode_attach_indirect(inode, alloc, block_len))
		error("failed to attach blocks to indirect inode");

	inode->i_flags = 0;
	inode->i_blocks_lo = (block_len + indirect_len) * info.block_size / 512;
	inode->i_size_lo = len;

	free_alloc(alloc);
}
