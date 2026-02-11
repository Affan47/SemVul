llist_clone(LList *list)
{
	LList *copy = xmalloc(sizeof(LList));
	LNode *entry;
	LNode *previous = NULL;

	copy->size = list->size;

	for (entry = list->first; entry != NULL; entry = entry->next) {
		LNode *new_entry = xmalloc(sizeof(LNode));
		new_entry->data = entry->data;
		new_entry->previous = previous;
		if (previous == NULL)
			copy->first = new_entry;
		else
			previous->next = new_entry;
		previous = new_entry;
	}

	copy->last = previous;
	if (previous == NULL)
		list->first = NULL;
	else
		previous->next = NULL;

	return copy;
}
