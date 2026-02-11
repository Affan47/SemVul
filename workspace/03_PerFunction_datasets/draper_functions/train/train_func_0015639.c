nilfs_find_uncommitted_extent(struct inode *inode,
					    sector_t start_blk,
					    sector_t *blkoff)
{
	unsigned int i;
	pgoff_t index;
	unsigned int nblocks_in_page;
	unsigned long length = 0;
	sector_t b;
	struct pagevec pvec;
	struct page *page;

	if (inode->i_mapping->nrpages == 0)
		return 0;

	index = start_blk >> (PAGE_CACHE_SHIFT - inode->i_blkbits);
	nblocks_in_page = 1U << (PAGE_CACHE_SHIFT - inode->i_blkbits);

	pagevec_init(&pvec, 0);

repeat:
	pvec.nr = find_get_pages_contig(inode->i_mapping, index, PAGEVEC_SIZE,
					pvec.pages);
	if (pvec.nr == 0)
		return length;

	if (length > 0 && pvec.pages[0]->index > index)
		goto out;

	b = pvec.pages[0]->index << (PAGE_CACHE_SHIFT - inode->i_blkbits);
	i = 0;
	do {
		page = pvec.pages[i];

		lock_page(page);
		if (page_has_buffers(page)) {
			struct buffer_head *bh, *head;

			bh = head = page_buffers(page);
			do {
				if (b < start_blk)
					continue;
				if (buffer_delay(bh)) {
					if (length == 0)
						*blkoff = b;
					length++;
				} else if (length > 0) {
					goto out_locked;
				}
			} while (++b, bh = bh->b_this_page, bh != head);
		} else {
			if (length > 0)
				goto out_locked;

			b += nblocks_in_page;
		}
		unlock_page(page);

	} while (++i < pagevec_count(&pvec));

	index = page->index + 1;
	pagevec_release(&pvec);
	cond_resched();
	goto repeat;

out_locked:
	unlock_page(page);
out:
	pagevec_release(&pvec);
	return length;
}
