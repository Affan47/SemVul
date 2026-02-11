dblhashNew(dblhash_ *h, unsigned int capacity)
{
    int i, sind = 0;

    capacity /= load_factor;

    for (i = 0; i < sizes_count; i++) {
        if (sizes[i] > capacity) {
			sind = i;
			break;
		}
	}

	h = calloc(sizeof(dblhash_), 1);
	ReturnNULLIf(h == NULL);

	h->records = calloc(sizes[sind], sizeof(record_));
	ReturnNULLIf(h->records == NULL);

	Debug("Creating Hash %p", h);
    h->records_count = 0;
    h->size_index = sind;

    return h;
}
