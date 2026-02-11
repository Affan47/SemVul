debug_kmalloc(size_t size, gfp_t flags)
{
	unsigned int rem, h_offset;
	struct debug_alloc_header *best, *bestprev, *prev, *h;
	void *p = NULL;
	if (!get_dap_lock()) {
		__release(dap_lock);
		return NULL;
	}
	h = (struct debug_alloc_header *)(debug_alloc_pool + dah_first);
	if (dah_first_call) {
		h->size = sizeof(debug_alloc_pool_aligned) - dah_overhead;
		dah_first_call = 0;
	}
	size = ALIGN(size, dah_align);
	prev = best = bestprev = NULL;
	while (1) {
		if (h->size >= size && (!best || h->size < best->size)) {
			best = h;
			bestprev = prev;
			if (h->size == size)
				break;
		}
		if (!h->next)
			break;
		prev = h;
		h = (struct debug_alloc_header *)(debug_alloc_pool + h->next);
	}
	if (!best)
		goto out;
	rem = best->size - size;

	if (best->next == 0 && bestprev == NULL && rem < dah_overhead)
		goto out;
	if (rem >= dah_overhead) {
		best->size = size;
		h_offset = ((char *)best - debug_alloc_pool) +
			   dah_overhead + best->size;
		h = (struct debug_alloc_header *)(debug_alloc_pool + h_offset);
		h->size = rem - dah_overhead;
		h->next = best->next;
	} else
		h_offset = best->next;
	best->caller = __builtin_return_address(0);
	dah_used += best->size;
	dah_used_max = max(dah_used, dah_used_max);
	if (bestprev)
		bestprev->next = h_offset;
	else
		dah_first = h_offset;
	p = (char *)best + dah_overhead;
	memset(p, POISON_INUSE, best->size - 1);
	*((char *)p + best->size - 1) = POISON_END;
out:
	spin_unlock(&dap_lock);
	return p;
}
