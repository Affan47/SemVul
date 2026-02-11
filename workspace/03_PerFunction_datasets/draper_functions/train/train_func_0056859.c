set_bh_page(struct buffer_head *bh,
		struct page *page, unsigned long offset)
{
	bh->b_page = page;
	BUG_ON(offset >= PAGE_SIZE);
	if (PageHighMem(page))


		bh->b_data = (char *)(0 + offset);
	else
		bh->b_data = page_address(page) + offset;
}
