brd_direct_access(struct block_device *bdev, sector_t sector,
			void __pmem **kaddr, unsigned long *pfn)
{
	struct brd_device *brd = bdev->bd_disk->private_data;
	struct page *page;

	if (!brd)
		return -ENODEV;
	page = brd_insert_page(brd, sector);
	if (!page)
		return -ENOSPC;
	*kaddr = (void __pmem *)page_address(page);
	*pfn = page_to_pfn(page);

	return PAGE_SIZE;
}
