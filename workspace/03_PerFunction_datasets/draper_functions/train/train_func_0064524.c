AUpvfree (AUpvlist list)
{
	assert(list);
	assert(list->items);

	if (list == AU_NULL_PVLIST)
		return AU_BAD_PVLIST;
	if (list->valid != _AU_VALID_PVLIST)
		return AU_BAD_PVLIST;

	if ((list->items != _AU_NULL_PVITEM) &&
		(list->items[0].valid == _AU_VALID_PVITEM))
	{
		free(list->items);
	}

	free(list);

	return _AU_SUCCESS;
}
