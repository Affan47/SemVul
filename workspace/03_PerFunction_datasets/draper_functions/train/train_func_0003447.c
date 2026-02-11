select_init(struct event_base *base)
{
	struct selectop *sop;

	if (!(sop = mm_calloc(1, sizeof(struct selectop))))
		return (NULL);

	if (select_resize(sop, SELECT_ALLOC_SIZE(32 + 1))) {
		select_free_selectop(sop);
		return (NULL);
	}

	evsig_init(base);

	return (sop);
}
