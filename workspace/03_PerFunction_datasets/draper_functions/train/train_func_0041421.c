btree_migratepage(struct address_space *mapping,
			struct page *newpage, struct page *page,
			enum migrate_mode mode)
{


	if (PageDirty(page))
		return -EAGAIN;


	if (page_has_private(page) &&
	    !try_to_release_page(page, GFP_KERNEL))
		return -EAGAIN;
	return migrate_page(mapping, newpage, page, mode);
}
