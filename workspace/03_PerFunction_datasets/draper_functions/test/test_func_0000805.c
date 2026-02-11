logfs_mtd_readpage(void *_sb, struct page *page)
{
	struct super_block *sb = _sb;
	int err;

	err = logfs_mtd_read(sb, page->index << PAGE_SHIFT, PAGE_SIZE,
			page_address(page));
	if (err == -EUCLEAN || err == -EBADMSG) {

		err = 0;

	}
	if (err) {
		ClearPageUptodate(page);
		SetPageError(page);
	} else {
		SetPageUptodate(page);
		ClearPageError(page);
	}
	unlock_page(page);
	return err;
}
