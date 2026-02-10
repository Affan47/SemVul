dax_load_hole(struct address_space *mapping, struct page *page,
							struct vm_fault *vmf)
{
	unsigned long size;
	struct inode *inode = mapping->host;
	if (!page)
		page = find_or_create_page(mapping, vmf->pgoff,
						GFP_KERNEL | __GFP_ZERO);
	if (!page)
		return VM_FAULT_OOM;

	size = (i_size_read(inode) + PAGE_SIZE - 1) >> PAGE_SHIFT;
	if (vmf->pgoff >= size) {
		unlock_page(page);
		page_cache_release(page);
		return VM_FAULT_SIGBUS;
	}

	vmf->page = page;
	return VM_FAULT_LOCKED;
}
