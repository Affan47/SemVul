f2fs_add_inline_entry(struct inode *dir, const struct qstr *name,
			struct inode *inode, nid_t ino, umode_t mode)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(dir);
	struct page *ipage;
	unsigned int bit_pos;
	f2fs_hash_t name_hash;
	size_t namelen = name->len;
	struct f2fs_inline_dentry *dentry_blk = NULL;
	struct f2fs_dentry_ptr d;
	int slots = GET_DENTRY_SLOTS(namelen);
	struct page *page = NULL;
	int err = 0;

	ipage = get_node_page(sbi, dir->i_ino);
	if (IS_ERR(ipage))
		return PTR_ERR(ipage);

	dentry_blk = inline_data_addr(ipage);
	bit_pos = room_for_filename(&dentry_blk->dentry_bitmap,
						slots, NR_INLINE_DENTRY);
	if (bit_pos >= NR_INLINE_DENTRY) {
		err = f2fs_convert_inline_dir(dir, ipage, dentry_blk);
		if (err)
			return err;
		err = -EAGAIN;
		goto out;
	}

	if (inode) {
		down_write(&F2FS_I(inode)->i_sem);
		page = init_inode_metadata(inode, dir, name, ipage);
		if (IS_ERR(page)) {
			err = PTR_ERR(page);
			goto fail;
		}
	}

	f2fs_wait_on_page_writeback(ipage, NODE);

	name_hash = f2fs_dentry_hash(name, NULL);
	make_dentry_ptr(NULL, &d, (void *)dentry_blk, 2);
	f2fs_update_dentry(ino, mode, &d, name, name_hash, bit_pos);

	set_page_dirty(ipage);


	if (inode) {
		F2FS_I(inode)->i_pino = dir->i_ino;
		update_inode(inode, page);
		f2fs_put_page(page, 1);
	}

	update_parent_metadata(dir, inode, 0);
fail:
	if (inode)
		up_write(&F2FS_I(inode)->i_sem);

	if (is_inode_flag_set(F2FS_I(dir), FI_UPDATE_DIR)) {
		update_inode(dir, ipage);
		clear_inode_flag(F2FS_I(dir), FI_UPDATE_DIR);
	}
out:
	f2fs_put_page(ipage, 1);
	return err;
}
