elist_link_replace(elist_t *list, link_t *old, link_t *new)
{
	elist_check(list);
	g_assert(old != NULL);
	g_assert(new != NULL);

	if G_UNLIKELY(old == new)
		return;

	elist_link_replace_internal(list, old, new, TRUE);

	*new = *old;
	old->next = old->prev = NULL;
}
