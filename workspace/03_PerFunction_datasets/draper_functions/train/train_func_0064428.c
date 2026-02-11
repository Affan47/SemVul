nilfs_end_page_io(struct page *page, int err)
{
	if (!page)
		return;

	if (buffer_nilfs_node(page_buffers(page)) && !PageWriteback(page)) {


		if (PageDirty(page)) {


			lock_page(page);
			if (nilfs_page_buffers_clean(page))
				__nilfs_clear_page_dirty(page);
			unlock_page(page);
		}
		return;
	}

	if (!err) {
		if (!nilfs_page_buffers_clean(page))
			__set_page_dirty_nobuffers(page);
		ClearPageError(page);
	} else {
		__set_page_dirty_nobuffers(page);
		SetPageError(page);
	}

	end_page_writeback(page);
}
