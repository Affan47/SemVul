l_add_tail(struct entry_space *es, struct ilist *l, struct entry *e)
{
	struct entry *tail = l_tail(es, l);

	e->next = INDEXER_NULL;
	e->prev = l->tail;

	if (tail)
		tail->next = l->tail = to_index(es, e);
	else
		l->head = l->tail = to_index(es, e);

	if (!e->sentinel)
		l->nr_elts++;
}
