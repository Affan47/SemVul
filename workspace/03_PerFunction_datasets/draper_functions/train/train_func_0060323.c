llist_to_null_terminated_array(LList *list)
{
	void **array = xmalloc((list->size+1) * sizeof(void *));
	LNode *entry = list->first;
	uint32_t index = 0;

	for (entry = list->first; entry != NULL; entry = entry->next)
		array[index++] = entry->data;
	array[index] = NULL;

	return array;
}
