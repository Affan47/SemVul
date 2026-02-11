mapper_has_next(Mapper *mapper)
{
	List *chain;
	ssize_t length;

	if (!mapper)
		return set_errno(EINVAL);


	mapper->next_chain_index = mapper->chain_index;
	mapper->next_item_index = mapper->item_index;

	if (mapper->next_chain_index == -1)
		++mapper->next_chain_index;

	while (mapper->next_chain_index < mapper->map->size && !mapper->map->chain[mapper->next_chain_index])
		++mapper->next_chain_index;

	if (mapper->next_chain_index == mapper->map->size)
		return 0;

	chain = mapper->map->chain[mapper->next_chain_index];


	if ((length = list_length_unlocked(chain)) == -1)
		return -1;

	if (++mapper->next_item_index < length)
		return 1;

	do
	{
		++mapper->next_chain_index;

		while (mapper->next_chain_index < mapper->map->size && !mapper->map->chain[mapper->next_chain_index])
			++mapper->next_chain_index;

		if (mapper->next_chain_index == mapper->map->size)
			return 0;

		chain = mapper->map->chain[mapper->next_chain_index];

		if ((length = list_length_unlocked(chain)) == -1)
			return -1;
	}
	while (length == 0);

	mapper->next_item_index = 0;

	return 1;
}
