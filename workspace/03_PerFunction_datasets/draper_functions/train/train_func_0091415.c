kmalloc_order(size_t size, gfp_t flags, unsigned int order)
{
	void *ret;
	struct page *page;

	flags |= __GFP_COMP;
	page = alloc_kmem_pages(flags, order);
	ret = page ? page_address(page) : NULL;
	kmemleak_alloc(ret, size, 1, flags);
	kasan_kmalloc_large(ret, size);
	return ret;
}
