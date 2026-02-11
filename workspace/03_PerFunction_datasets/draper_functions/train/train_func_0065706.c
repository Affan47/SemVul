ext2_find_entry (struct inode * dir,
			struct qstr *child, struct page ** res_page)
{
	const char *name = child->name;
	int namelen = child->len;
	unsigned reclen = EXT2_DIR_REC_LEN(namelen);
	unsigned long start, n;
	unsigned long npages = dir_pages(dir);
	struct page *page = NULL;
	struct ext2_inode_info *ei = EXT2_I(dir);
	ext2_dirent * de;
	int dir_has_error = 0;

	if (npages == 0)
		goto out;


	*res_page = NULL;

	start = ei->i_dir_start_lookup;
	if (start >= npages)
		start = 0;
	n = start;
	do {
		char *kaddr;
		page = ext2_get_page(dir, n, dir_has_error);
		if (!IS_ERR(page)) {
			kaddr = page_address(page);
			de = (ext2_dirent *) kaddr;
			kaddr += ext2_last_byte(dir, n) - reclen;
			while ((char *) de <= kaddr) {
				if (de->rec_len == 0) {
					ext2_error(dir->i_sb, __func__,
						"zero-length directory entry");
					ext2_put_page(page);
					goto out;
				}
				if (ext2_match (namelen, name, de))
					goto found;
				de = ext2_next_entry(de);
			}
			ext2_put_page(page);
		} else
			dir_has_error = 1;

		if (++n >= npages)
			n = 0;

		if (unlikely(n > (dir->i_blocks >> (PAGE_CACHE_SHIFT - 9)))) {
			ext2_error(dir->i_sb, __func__,
				"dir %lu size %lld exceeds block count %llu",
				dir->i_ino, dir->i_size,
				(unsigned long long)dir->i_blocks);
			goto out;
		}
	} while (n != start);
out:
	return NULL;

found:
	*res_page = page;
	ei->i_dir_start_lookup = n;
	return de;
}
