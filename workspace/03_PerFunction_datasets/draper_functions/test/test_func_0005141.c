_dico_list_remove_item(struct dico_list *list, struct list_entry *p,
		       void **pptr)
{
    struct list_entry *prev;

    _iterator_advance(list->itr, p);

    prev = p->prev;
    if (prev)
	prev->next = p->next;
    else
	list->head = list->head->next;

    if (p->next)
	p->next->prev = prev;
    else
	list->tail = prev;

    free(p);
    list->count--;

    if (pptr)
	*pptr = p->data;
    else if (list->free_item)
	list->free_item (p->data, list->free_data);
}
