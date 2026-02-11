location_to_obj(struct page *page, unsigned long obj_idx)
{
	unsigned long obj;

	if (!page) {
		BUG_ON(obj_idx);
		return NULL;
	}

	obj = page_to_pfn(page) << OBJ_INDEX_BITS;
	obj |= ((obj_idx) & OBJ_INDEX_MASK);
	obj <<= OBJ_TAG_BITS;

	return (void *)obj;
}
