linked_list_create_from_enumerator(enumerator_t *enumerator)
{
	linked_list_t *list;
	void *item;

	list = linked_list_create();

	while (enumerator->enumerate(enumerator, &item))
	{
		list->insert_last(list, item);
	}
	enumerator->destroy(enumerator);

	return list;
}
