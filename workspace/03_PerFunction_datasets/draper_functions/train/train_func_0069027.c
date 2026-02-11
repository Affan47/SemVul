list_sort_unlocked(List *list, list_cmp_t *cmp)
{
	if (!list)
		return set_errnull(EINVAL);

	if (!list->list || !list->length)
		return set_errnull(EINVAL);

	((list->length >= 10000) ? hsort : qsort)(list->list, list->length, sizeof list->list[0], cmp);

	return list;
}
