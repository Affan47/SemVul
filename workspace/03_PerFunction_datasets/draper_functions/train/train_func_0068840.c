llist_add_first(LList *list, void *data)
{
	LNode *entry = xmalloc(sizeof(LNode));
	entry->data = data;

	if (list->size == 0) {
		entry->next = NULL;
		entry->previous = NULL;
		list->first = list->last = entry;
	} else {
		entry->next = list->first;
		entry->previous = NULL;
		list->first->previous = entry;
		list->first = entry;
	}
	list->size++;
}
