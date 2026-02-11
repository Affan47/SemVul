bm_realloc_pages(struct drbd_bitmap *b, unsigned long want)
{
	struct page **old_pages = b->bm_pages;
	struct page **new_pages, *page;
	unsigned int i, bytes, vmalloced = 0;
	unsigned long have = b->bm_number_of_pages;

	BUG_ON(have == 0 && old_pages != NULL);
	BUG_ON(have != 0 && old_pages == NULL);

	if (have == want)
		return old_pages;


	bytes = sizeof(struct page *)*want;
	new_pages = kzalloc(bytes, GFP_NOIO | __GFP_NOWARN);
	if (!new_pages) {
		new_pages = __vmalloc(bytes,
				GFP_NOIO | __GFP_HIGHMEM | __GFP_ZERO,
				PAGE_KERNEL);
		if (!new_pages)
			return NULL;
		vmalloced = 1;
	}

	if (want >= have) {
		for (i = 0; i < have; i++)
			new_pages[i] = old_pages[i];
		for (; i < want; i++) {
			page = alloc_page(GFP_NOIO | __GFP_HIGHMEM);
			if (!page) {
				bm_free_pages(new_pages + have, i - have);
				bm_vk_free(new_pages, vmalloced);
				return NULL;
			}


			bm_store_page_idx(page, i);
			new_pages[i] = page;
		}
	} else {
		for (i = 0; i < want; i++)
			new_pages[i] = old_pages[i];


	}

	if (vmalloced)
		b->bm_flags |= BM_P_VMALLOCED;
	else
		b->bm_flags &= ~BM_P_VMALLOCED;

	return new_pages;
}
