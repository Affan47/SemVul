xfl_delete_slot(struct xfreelist *fl, size_t idx)
{
	g_assert(size_is_positive(fl->count));
	g_assert(size_is_non_negative(idx) && idx < fl->count);
	g_assert(fl->count >= fl->sorted);
	g_assert(mutex_is_owned(&fl->lock));

	fl->count--;
	if (idx < fl->sorted)
		fl->sorted--;
	xstats.freelist_blocks--;
	xstats.freelist_memory -= fl->blocksize;

	if (idx < fl->count) {
		memmove(&fl->pointers[idx], &fl->pointers[idx + 1],
			(fl->count - idx) * sizeof(fl->pointers[0]));
	}


	fl->pointers[fl->count] = XM_INVALID_PTR;
	xfl_count_decreased(fl, TRUE);
}
