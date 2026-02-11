make_empty_inline_dir(struct inode *inode, struct inode *parent,
							struct page *ipage)
{
	struct f2fs_inline_dentry *dentry_blk;
	struct f2fs_dentry_ptr d;

	dentry_blk = inline_data_addr(ipage);

	make_dentry_ptr(NULL, &d, (void *)dentry_blk, 2);
	do_make_empty_dir(inode, parent, &d);

	set_page_dirty(ipage);


	if (i_size_read(inode) < MAX_INLINE_DATA) {
		i_size_write(inode, MAX_INLINE_DATA);
		set_inode_flag(F2FS_I(inode), FI_UPDATE_DIR);
	}
	return 0;
}
