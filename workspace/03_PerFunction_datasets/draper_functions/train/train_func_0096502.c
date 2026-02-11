ck_shrink(ckhunk_t *ck, size_t size)
{
	size_t nsize, used;
	sigset_t set;

	ckhunk_check(ck);

	if (NULL == ck)
		return FALSE;

	size = MAX(1, size);
	nsize = round_pagesize(size);

	if (ck->size <= nsize)
		return FALSE;

	used = round_pagesize(ptr_diff(ck->avail, ck->arena));
	nsize = used > nsize ? used : nsize;


	g_assert(ck->size > nsize);

	if (!signal_enter_critical(&set))
		return FALSE;

	if (ck->read_only)
		ck_protect(ck, PROT_READ | PROT_WRITE);

	vmm_shrink(ck->arena, ck->size, nsize);
	ck->size = nsize;
	ck->end = ck->arena + ck->size;

	if (ck->read_only)
		ck_protect(ck, PROT_READ);

	g_assert(ptr_cmp(ck->end, ck->avail) >= 0);

	signal_leave_critical(&set);
	return TRUE;
}
