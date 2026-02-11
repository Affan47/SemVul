GMT_alloc_memory (void **ptr, GMT_LONG n, GMT_LONG n_alloc, size_t element_size, char *module)
#endif
{


	if (n_alloc == 0) {
		n_alloc = (n == 0) ? GMT_min_meminc : n;
		*ptr = NULL;
	}
	else if (n == 0 && n_alloc > 0)
		n = n_alloc;
	else if (n < n_alloc)
		return (n_alloc);
	else {
		size_t add;
		add = MAX (GMT_min_meminc, MIN (n_alloc/2, GMT_max_meminc));
		n_alloc = MIN (add + n_alloc, LONG_MAX);
		if (n >= n_alloc) n_alloc = n + 1;
	}


	*ptr = GMT_memory (*ptr, n_alloc, element_size, module);
	return (n_alloc);
}
