eslist_link_insert_after_internal(eslist_t *list, slink_t *siblk, slink_t *lk)
{
	g_assert(size_is_positive(list->count));
	eslist_invariant(list);

	if G_UNLIKELY(list->tail == siblk)
		list->tail = lk;

	lk->next = siblk->next;
	siblk->next = lk;

	list->count++;
	safety_assert(eslist_invariant(list));
	safety_assert(eslist_length(list->head) == list->count);
}
