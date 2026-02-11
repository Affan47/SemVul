wbuf_read(struct super_block *sb, u64 ofs, size_t len, void *buf)
{
	pgoff_t index = ofs >> PAGE_SHIFT;
	struct page *page;
	long offset = ofs & (PAGE_SIZE-1);
	long copylen;

	while (len) {
		copylen = min((ulong)len, PAGE_SIZE - offset);

		page = get_mapping_page(sb, index, 1);
		if (IS_ERR(page))
			return PTR_ERR(page);
		memcpy(buf, page_address(page) + offset, copylen);
		page_cache_release(page);

		buf += copylen;
		len -= copylen;
		offset = 0;
		index++;
	}
	return 0;
}
