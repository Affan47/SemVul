ufs_empty_dir(struct inode * inode)
{
	struct super_block *sb = inode->i_sb;
	struct page *page = NULL;
	unsigned long i, npages = dir_pages(inode);

	for (i = 0; i < npages; i++) {
		char *kaddr;
		struct ufs_dir_entry *de;
		page = ufs_get_page(inode, i);

		if (IS_ERR(page))
			continue;

		kaddr = page_address(page);
		de = (struct ufs_dir_entry *)kaddr;
		kaddr += ufs_last_byte(inode, i) - UFS_DIR_REC_LEN(1);

		while ((char *)de <= kaddr) {
			if (de->d_reclen == 0) {
				ufs_error(inode->i_sb, __func__,
					"zero-length directory entry: "
					"kaddr=%p, de=%p\n", kaddr, de);
				goto not_empty;
			}
			if (de->d_ino) {
				u16 namelen=ufs_get_de_namlen(sb, de);

				if (de->d_name[0] != '.')
					goto not_empty;
				if (namelen > 2)
					goto not_empty;
				if (namelen < 2) {
					if (inode->i_ino !=
					    fs32_to_cpu(sb, de->d_ino))
						goto not_empty;
				} else if (de->d_name[1] != '.')
					goto not_empty;
			}
			de = ufs_next_entry(sb, de);
		}
		ufs_put_page(page);
	}
	return 1;

not_empty:
	ufs_put_page(page);
	return 0;
}
