elist_link_remove_internal(elist_t *list, link_t *lk)
{
	g_assert(size_is_positive(list->count));
	elist_invariant(list);

	if G_UNLIKELY(list->head == lk)
		list->head = lk->next;

	if G_UNLIKELY(list->tail == lk)
		list->tail = lk->prev;

	if (lk->prev != NULL)
		lk->prev->next = lk->next;
	if (lk->next != NULL)
		lk->next->prev = lk->prev;

	lk->next = lk->prev = NULL;
	list->count--;

	safety_assert(elist_invariant(list));
	safety_assert(elist_length(list->head) == list->count);
}
