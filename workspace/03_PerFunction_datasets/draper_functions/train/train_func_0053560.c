imemalign(void **memptr, size_t alignment, size_t size, size_t min_alignment)
{
	int ret;
	size_t usize;
	void *result;

	assert(min_alignment != 0);

	if (malloc_init()) {
		result = NULL;
		goto label_oom;
	} else {
		if (size == 0)
			size = 1;


		if (((alignment - 1) & alignment) != 0
		    || (alignment < min_alignment)) {
			if (config_xmalloc && opt_xmalloc) {
				malloc_write("<jemalloc>: Error allocating "
				    "aligned memory: invalid alignment\n");
				abort();
			}
			result = NULL;
			ret = EINVAL;
			goto label_return;
		}

		usize = sa2u(size, alignment);
		if (usize == 0) {
			result = NULL;
			goto label_oom;
		}

		if (config_prof && opt_prof) {
			prof_thr_cnt_t *cnt;

			PROF_ALLOC_PREP(2, usize, cnt);
			result = imemalign_prof(alignment, usize, cnt);
		} else
			result = ipalloc(usize, alignment, false);
		if (result == NULL)
			goto label_oom;
	}

	*memptr = result;
	ret = 0;
label_return:
	if (config_stats && result != NULL) {
		assert(usize == isalloc(result, config_prof));
		thread_allocated_tsd_get()->allocated += usize;
	}
	UTRACE(0, size, result);
	return (ret);
label_oom:
	assert(result == NULL);
	if (config_xmalloc && opt_xmalloc) {
		malloc_write("<jemalloc>: Error allocating aligned memory: "
		    "out of memory\n");
		abort();
	}
	ret = ENOMEM;
	goto label_return;
}
