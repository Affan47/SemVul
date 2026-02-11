free_buffers(struct page *page)
{
	struct buffer_head *bh;

	if (!PagePrivate(page))
		return;

	bh = page_buffers(page);
	while (bh) {
		struct buffer_head *next = bh->b_this_page;
		free_buffer_head(bh);
		bh = next;
	}
	__clear_page_buffers(page);
	put_page(page);
}
