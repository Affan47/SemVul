btrfs_copy_from_user(loff_t pos, int num_pages,
					 size_t write_bytes,
					 struct page **prepared_pages,
					 struct iov_iter *i)
{
	size_t copied = 0;
	size_t total_copied = 0;
	int pg = 0;
	int offset = pos & (PAGE_CACHE_SIZE - 1);

	while (write_bytes > 0) {
		size_t count = min_t(size_t,
				     PAGE_CACHE_SIZE - offset, write_bytes);
		struct page *page = prepared_pages[pg];


		copied = iov_iter_copy_from_user_atomic(page, i, offset, count);


		flush_dcache_page(page);


		if (!PageUptodate(page) && copied < count)
			copied = 0;

		iov_iter_advance(i, copied);
		write_bytes -= copied;
		total_copied += copied;


		if (unlikely(copied == 0))
			break;

		if (copied < PAGE_CACHE_SIZE - offset) {
			offset += copied;
		} else {
			pg++;
			offset = 0;
		}
	}
	return total_copied;
}
