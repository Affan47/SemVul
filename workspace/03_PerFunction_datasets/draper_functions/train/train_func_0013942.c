elist_nth_next_data(const elist_t *list, const link_t *lk, size_t n)
{
	link_t *l;

	elist_check(list);
	g_assert(lk != NULL);
	g_assert(size_is_non_negative(n));

	l = elist_nth_next(lk, n);
	return NULL == l ? NULL : ptr_add_offset(l, -list->offset);
}
