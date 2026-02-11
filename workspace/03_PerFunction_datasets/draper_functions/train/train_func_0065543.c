text_value_cache(ulong vaddr, uint32_t value, uint32_t *valptr)
{
	int i;
	struct text_cache *tc;

	if (!is_kernel_text(vaddr))
		return FALSE;

	tc = &text_cache;

	if (!tc->cache) {
		if (!(tc->cache = (struct text_cache_entry *)
		    malloc(sizeof(struct text_cache_entry) * TEXT_CACHE)))
			return FALSE;
		BZERO(tc->cache, sizeof(struct text_cache_entry) * TEXT_CACHE);
		tc->index = 0;
		tc->entries = TEXT_CACHE;
	}

	if (value) {
		for (i = 0; i < tc->entries; i++) {
			if (tc->cache[i].vaddr == vaddr)
				return TRUE;
		}

		i = tc->index;
		tc->cache[i].vaddr = vaddr;
		tc->cache[i].value = value;
		tc->index++;
		if (tc->index == MAX_TEXT_CACHE) {
			tc->index = 0;
		} else if (tc->index == tc->entries) {
			struct text_cache_entry *old_cache;

			old_cache = tc->cache;
			if ((tc->cache = (struct text_cache_entry *)
                    	    realloc(old_cache, sizeof(struct text_cache_entry) *
			    (TEXT_CACHE+tc->entries)))) {
				BZERO(&tc->cache[tc->index],
				    sizeof(struct text_cache_entry) *
				    TEXT_CACHE);
				tc->entries += TEXT_CACHE;
			} else {
				tc->cache = old_cache;
				tc->index = 0;
			}
		}
		return TRUE;
	}

	if (valptr) {
		tc->refs++;

		for (i = 0; i < tc->entries; i++) {
			if (!tc->cache[i].vaddr)
				return FALSE;

			if (tc->cache[i].vaddr == vaddr) {
				*valptr = tc->cache[i].value;
				tc->hits++;
				return TRUE;
			}
		}
	}

	return FALSE;
}
