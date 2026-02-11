recover_data(struct f2fs_sb_info *sbi,
				struct list_head *head, int type)
{
	unsigned long long cp_ver = cur_cp_version(F2FS_CKPT(sbi));
	struct curseg_info *curseg;
	struct page *page = NULL;
	int err = 0;
	block_t blkaddr;


	curseg = CURSEG_I(sbi, type);
	blkaddr = NEXT_FREE_BLKADDR(sbi, curseg);

	while (1) {
		struct fsync_inode_entry *entry;

		if (!is_valid_blkaddr(sbi, blkaddr, META_POR))
			break;

		ra_meta_pages_cond(sbi, blkaddr);

		page = get_tmp_page(sbi, blkaddr);

		if (cp_ver != cpver_of_node(page)) {
			f2fs_put_page(page, 1);
			break;
		}

		entry = get_fsync_inode(head, ino_of_node(page));
		if (!entry)
			goto next;


		if (entry->last_inode == blkaddr)
			recover_inode(entry->inode, page);
		if (entry->last_dentry == blkaddr) {
			err = recover_dentry(entry->inode, page);
			if (err) {
				f2fs_put_page(page, 1);
				break;
			}
		}
		err = do_recover_data(sbi, entry->inode, page, blkaddr);
		if (err) {
			f2fs_put_page(page, 1);
			break;
		}

		if (entry->blkaddr == blkaddr) {
			iput(entry->inode);
			list_del(&entry->list);
			kmem_cache_free(fsync_entry_slab, entry);
		}
next:

		blkaddr = next_blkaddr_of_node(page);
		f2fs_put_page(page, 1);
	}
	if (!err)
		allocate_new_segments(sbi);
	return err;
}
