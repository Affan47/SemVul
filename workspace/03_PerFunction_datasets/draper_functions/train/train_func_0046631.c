recover_inline_data(struct inode *inode, struct page *npage)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct f2fs_inode *ri = NULL;
	void *src_addr, *dst_addr;
	struct page *ipage;


	if (IS_INODE(npage))
		ri = F2FS_INODE(npage);

	if (f2fs_has_inline_data(inode) &&
			ri && (ri->i_inline & F2FS_INLINE_DATA)) {
process_inline:
		ipage = get_node_page(sbi, inode->i_ino);
		f2fs_bug_on(sbi, IS_ERR(ipage));

		f2fs_wait_on_page_writeback(ipage, NODE);

		src_addr = inline_data_addr(npage);
		dst_addr = inline_data_addr(ipage);
		memcpy(dst_addr, src_addr, MAX_INLINE_DATA);

		set_inode_flag(F2FS_I(inode), FI_INLINE_DATA);
		set_inode_flag(F2FS_I(inode), FI_DATA_EXIST);

		update_inode(inode, ipage);
		f2fs_put_page(ipage, 1);
		return true;
	}

	if (f2fs_has_inline_data(inode)) {
		ipage = get_node_page(sbi, inode->i_ino);
		f2fs_bug_on(sbi, IS_ERR(ipage));
		if (!truncate_inline_inode(ipage, 0))
			return false;
		f2fs_clear_inline_inode(inode);
		update_inode(inode, ipage);
		f2fs_put_page(ipage, 1);
	} else if (ri && (ri->i_inline & F2FS_INLINE_DATA)) {
		if (truncate_blocks(inode, 0, false))
			return false;
		goto process_inline;
	}
	return false;
}
