debug_kfree(void *p)
{
	struct debug_alloc_header *h;
	unsigned int h_offset;
	if (!p)
		return;
	if ((char *)p < debug_alloc_pool ||
	    (char *)p >= debug_alloc_pool + sizeof(debug_alloc_pool_aligned)) {
		kfree(p);
		return;
	}
	if (!get_dap_lock()) {
		__release(dap_lock);
		return;
	}
	h = (struct debug_alloc_header *)((char *)p - dah_overhead);
	memset(p, POISON_FREE, h->size - 1);
	*((char *)p + h->size - 1) = POISON_END;
	h->caller = NULL;
	dah_used -= h->size;
	h_offset = (char *)h - debug_alloc_pool;
	if (h_offset < dah_first) {
		h->next = dah_first;
		dah_first = h_offset;
	} else {
		struct debug_alloc_header *prev;
		unsigned int prev_offset;
		prev = (struct debug_alloc_header *)(debug_alloc_pool +
						     dah_first);
		while (1) {
			if (!prev->next || prev->next > h_offset)
				break;
			prev = (struct debug_alloc_header *)
				(debug_alloc_pool + prev->next);
		}
		prev_offset = (char *)prev - debug_alloc_pool;
		if (prev_offset + dah_overhead + prev->size == h_offset) {
			prev->size += dah_overhead + h->size;
			memset(h, POISON_FREE, dah_overhead - 1);
			*((char *)h + dah_overhead - 1) = POISON_END;
			h = prev;
			h_offset = prev_offset;
		} else {
			h->next = prev->next;
			prev->next = h_offset;
		}
	}
	if (h_offset + dah_overhead + h->size == h->next) {
		struct debug_alloc_header *next;
		next = (struct debug_alloc_header *)
			(debug_alloc_pool + h->next);
		h->size += dah_overhead + next->size;
		h->next = next->next;
		memset(next, POISON_FREE, dah_overhead - 1);
		*((char *)next + dah_overhead - 1) = POISON_END;
	}
	spin_unlock(&dap_lock);
}
