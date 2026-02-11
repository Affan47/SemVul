nilfs_empty_dir(struct inode *inode)
{
	struct page *page = NULL;
	unsigned long i, npages = dir_pages(inode);

	for (i = 0; i < npages; i++) {
		char *kaddr;
		struct nilfs_dir_entry *de;

		page = nilfs_get_page(inode, i);
		if (IS_ERR(page))
			continue;

		kaddr = page_address(page);
		de = (struct nilfs_dir_entry *)kaddr;
		kaddr += nilfs_last_byte(inode, i) - NILFS_DIR_REC_LEN(1);

		while ((char *)de <= kaddr) {
			if (de->rec_len == 0) {
				nilfs_error(inode->i_sb, __func__,
					    "zero-length directory entry "
					    "(kaddr=%p, de=%p)\n", kaddr, de);
				goto not_empty;
			}
			if (de->inode != 0) {

				if (de->name[0] != '.')
					goto not_empty;
				if (de->name_len > 2)
					goto not_empty;
				if (de->name_len < 2) {
					if (de->inode !=
					    cpu_to_le64(inode->i_ino))
						goto not_empty;
				} else if (de->name[1] != '.')
					goto not_empty;
			}
			de = nilfs_next_entry(de);
		}
		nilfs_put_page(page);
	}
	return 1;

not_empty:
	nilfs_put_page(page);
	return 0;
}
