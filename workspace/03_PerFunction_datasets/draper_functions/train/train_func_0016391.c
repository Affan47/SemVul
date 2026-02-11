kfree(const void *x)
{
	struct page *page;
	void *object = (void *)x;

	trace_kfree(_RET_IP_, x);

	if (unlikely(ZERO_OR_NULL_PTR(x)))
		return;

	page = virt_to_head_page(x);
	if (unlikely(!PageSlab(page))) {
		BUG_ON(!PageCompound(page));
		kfree_hook(x);
		__free_kmem_pages(page, compound_order(page));
		return;
	}
	slab_free(page->slab_cache, page, object, NULL, 1, _RET_IP_);
}
