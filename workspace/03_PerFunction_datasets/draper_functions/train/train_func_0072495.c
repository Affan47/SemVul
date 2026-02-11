bm_set_full_words_within_one_page(struct drbd_bitmap *b,
		int page_nr, int first_word, int last_word)
{
	int i;
	int bits;
	int changed = 0;
	unsigned long *paddr = kmap_atomic(b->bm_pages[page_nr]);
	for (i = first_word; i < last_word; i++) {
		bits = hweight_long(paddr[i]);
		paddr[i] = ~0UL;
		changed += BITS_PER_LONG - bits;
	}
	kunmap_atomic(paddr);
	if (changed) {


		bm_set_page_lazy_writeout(b->bm_pages[page_nr]);
		b->bm_set += changed;
	}
}
