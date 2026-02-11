grow_inode(struct inode *inode, u64 bix, level_t level)
{
	struct logfs_inode *li = logfs_inode(inode);
	u8 height = (__force u8)level;
	struct page *page;
	struct write_control wc = {
		.flags = WF_WRITE,
	};
	int err;

	BUG_ON(height > 5 || li->li_height > 5);
	while (height > li->li_height || bix >= maxbix(li->li_height)) {
		page = logfs_get_write_page(inode, I0_BLOCKS + 1,
				LEVEL(li->li_height + 1));
		if (!page)
			return -ENOMEM;
		logfs_read_empty(page);
		alloc_indirect_block(inode, page, 1);
		block_set_pointer(page, 0, li->li_data[INDIRECT_INDEX]);
		err = logfs_write_i0(inode, page, &wc);
		logfs_put_write_page(page);
		if (err)
			return err;
		li->li_data[INDIRECT_INDEX] = wc.ofs;
		wc.ofs = 0;
		li->li_height++;
		logfs_set_alias(inode->i_sb, li->li_block, INODE_HEIGHT_OFS);
	}
	return 0;
}
