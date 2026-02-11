create_delta_index(const void *buf, unsigned long bufsize)
{
	unsigned int i, hsize, hmask, entries, prev_val, *hash_count;
	const unsigned char *data, *buffer = buf;
	struct delta_index *index;
	struct index_entry *entry, **hash;
	void *mem;
	unsigned long memsize;

	if (!buf || !bufsize)
		return NULL;


	entries = (bufsize - 1)  / RABIN_WINDOW;
	hsize = entries / 4;
	for (i = 4; (1u << i) < hsize && i < 31; i++);
	hsize = 1 << i;
	hmask = hsize - 1;


	memsize = sizeof(*index) +
		  sizeof(*hash) * hsize +
		  sizeof(*entry) * entries;
	mem = malloc(memsize);
	if (!mem)
		return NULL;
	index = mem;
	mem = index + 1;
	hash = mem;
	mem = hash + hsize;
	entry = mem;

	index->src_buf = buf;
	index->src_size = bufsize;
	index->hash_mask = hmask;
	memset(hash, 0, hsize * sizeof(*hash));


	hash_count = calloc(hsize, sizeof(*hash_count));
	if (!hash_count) {
		free(index);
		return NULL;
	}


	prev_val = ~0;
	for (data = buffer + entries * RABIN_WINDOW - RABIN_WINDOW;
	     data >= buffer;
	     data -= RABIN_WINDOW) {
		unsigned int val = 0;
		for (i = 1; i <= RABIN_WINDOW; i++)
			val = ((val << 8) | data[i]) ^ T[val >> RABIN_SHIFT];
		if (val == prev_val) {

			entry[-1].ptr = data + RABIN_WINDOW;
		} else {
			prev_val = val;
			i = val & hmask;
			entry->ptr = data + RABIN_WINDOW;
			entry->val = val;
			entry->next = hash[i];
			hash[i] = entry++;
			hash_count[i]++;
		}
	}


	for (i = 0; i < hsize; i++) {
		if (hash_count[i] < HASH_LIMIT)
			continue;
		entry = hash[i];
		do {
			struct index_entry *keep = entry;
			int skip = hash_count[i] / HASH_LIMIT / 2;
			do {
				entry = entry->next;
			} while(--skip && entry);
			keep->next = entry;
		} while(entry);
	}
	free(hash_count);

	return index;
}
