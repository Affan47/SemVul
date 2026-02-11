xmalloc_free_pages(void *p, size_t len,
	void **head, size_t *head_len,
	void **tail, size_t *tail_len)
{
	void *page;
	const void *end;
	const void *vend;
	size_t plen, hlen, tlen;

	page = deconstify_pointer(vmm_page_start(p));
	end = ptr_add_offset(p, len);

	if (ptr_cmp(page, p) < 0) {
		page = ptr_add_offset(page, xmalloc_pagesize);
		if (ptr_cmp(page, end) >= 0)
			return FALSE;
	}


	vend = vmm_page_start(end);

	g_assert(ptr_cmp(page, vend) <= 0);

	if (vend == page)
		return FALSE;


	hlen = ptr_diff(page, p);
	if (hlen != 0 && hlen < XMALLOC_SPLIT_MIN)
		return FALSE;

	tlen = ptr_diff(end, vend);
	if (tlen != 0 && tlen < XMALLOC_SPLIT_MIN)
		return FALSE;

	*head = deconstify_pointer(p);
	*head_len = hlen;
	*tail = deconstify_pointer(vend);
	*tail_len = tlen;


	if (xmalloc_debugging(1)) {
		t_debug(
			"XM releasing VMM [%p, %p[ (%zu bytes) within [%p, %p[ (%zu bytes)",
			page, vend, ptr_diff(vend, page), p, end, len);
	}

	plen = ptr_diff(vend, page);
	vmm_core_free(page, plen);

	xstats.free_vmm_core++;
	xstats.vmm_freed_pages += vmm_page_count(plen);

	return TRUE;
}
