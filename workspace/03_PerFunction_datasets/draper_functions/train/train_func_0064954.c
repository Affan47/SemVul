hugetlbfs_read_actor(struct page *page, unsigned long offset,
			struct iov_iter *to, unsigned long size)
{
	size_t copied = 0;
	int i, chunksize;


	i = offset >> PAGE_CACHE_SHIFT;
	offset = offset & ~PAGE_CACHE_MASK;

	while (size) {
		size_t n;
		chunksize = PAGE_CACHE_SIZE;
		if (offset)
			chunksize -= offset;
		if (chunksize > size)
			chunksize = size;
		n = copy_page_to_iter(&page[i], offset, chunksize, to);
		copied += n;
		if (n != chunksize)
			return copied;
		offset = 0;
		size -= chunksize;
		i++;
	}
	return copied;
}
