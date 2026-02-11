xfl_sort(struct xfreelist *fl)
{
	size_t unsorted;
	void **ary = fl->pointers;
	size_t x = fl->sorted;

	g_assert(mutex_is_owned(&fl->lock));


	unsorted = fl->count - x;

	if G_UNLIKELY(0 == unsorted)
		return;

	g_assert(size_is_positive(unsorted));


	if G_LIKELY(unsorted > 1) {
		xstats.freelist_partial_sorting++;
		xqsort(&ary[x], unsorted, sizeof ary[0], xfl_ptr_cmp);
		assert_xfl_sorted(fl, x, unsorted, "after xqsort");
	}


	if (0 != x && 0 < xm_ptr_cmp(ary[x - 1], ary[x])) {


		xstats.freelist_full_sorting++;
		xqsort(ary, fl->count, sizeof ary[0], xfl_ptr_cmp);
		assert_xfl_sorted(fl, 0, fl->count, "after full qsort");
	} else {
		xstats.freelist_avoided_sorting++;
		assert_xfl_sorted(fl, 0, fl->count, "after nosort");
	}

	fl->sorted = fl->count;

	if (xmalloc_debugging(1)) {
		t_debug("XM sorted %zu items from freelist #%zu (%zu bytes)",
			fl->count, xfl_index(fl), fl->blocksize);
	}
}
