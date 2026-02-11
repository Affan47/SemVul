ast_heap_create(unsigned int init_height, ast_heap_cmp_fn cmp_fn,
		ssize_t index_offset)
#endif
{
	struct ast_heap *h;

	if (!cmp_fn) {
		ast_log(LOG_ERROR, "A comparison function must be provided\n");
		return NULL;
	}

	if (!init_height) {
		init_height = 8;
	}

	if (!(h =
#ifdef MALLOC_DEBUG
			__ast_calloc(1, sizeof(*h), file, lineno, func)
#else
			ast_calloc(1, sizeof(*h))
#endif
		)) {
		return NULL;
	}

	h->cmp_fn = cmp_fn;
	h->index_offset = index_offset;
	h->avail_len = (1 << init_height) - 1;

	if (!(h->heap =
#ifdef MALLOC_DEBUG
			__ast_calloc(1, h->avail_len * sizeof(void *), file, lineno, func)
#else
			ast_calloc(1, h->avail_len * sizeof(void *))
#endif
		)) {
		ast_free(h);
		return NULL;
	}

	ast_rwlock_init(&h->lock);

	return h;
}
