pad_full_pages(struct logfs_area *area)
{
	struct super_block *sb = area->a_sb;
	struct logfs_super *super = logfs_super(sb);
	u64 ofs = dev_ofs(sb, area->a_segno, area->a_used_bytes);
	u32 len = super->s_segsize - area->a_used_bytes;
	pgoff_t index = PAGE_CACHE_ALIGN(ofs) >> PAGE_CACHE_SHIFT;
	pgoff_t no_indizes = len >> PAGE_CACHE_SHIFT;
	struct page *page;

	while (no_indizes) {
		page = get_mapping_page(sb, index, 0);
		BUG_ON(!page);
		SetPageUptodate(page);
		memset(page_address(page), 0xff, PAGE_CACHE_SIZE);
		if (!PagePrivate(page)) {
			SetPagePrivate(page);
			page_cache_get(page);
		}
		page_cache_release(page);
		index++;
		no_indizes--;
	}
}
