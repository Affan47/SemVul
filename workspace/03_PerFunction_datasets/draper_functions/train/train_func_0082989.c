kimage_alloc_normal_control_pages(struct kimage *image,
							unsigned int order)
{


	struct list_head extra_pages;
	struct page *pages;
	unsigned int count;

	count = 1 << order;
	INIT_LIST_HEAD(&extra_pages);


	do {
		unsigned long pfn, epfn, addr, eaddr;

		pages = kimage_alloc_pages(KEXEC_CONTROL_MEMORY_GFP, order);
		if (!pages)
			break;
		pfn   = page_to_pfn(pages);
		epfn  = pfn + count;
		addr  = pfn << PAGE_SHIFT;
		eaddr = epfn << PAGE_SHIFT;
		if ((epfn >= (KEXEC_CONTROL_MEMORY_LIMIT >> PAGE_SHIFT)) ||
			      kimage_is_destination_range(image, addr, eaddr)) {
			list_add(&pages->lru, &extra_pages);
			pages = NULL;
		}
	} while (!pages);

	if (pages) {

		list_add(&pages->lru, &image->control_pages);


	}


	kimage_free_page_list(&extra_pages);

	return pages;
}
