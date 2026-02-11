engine_list_cleanup(void)
	{
	ENGINE *iterator = engine_list_head;

	while(iterator != NULL)
		{
		ENGINE_remove(iterator);
		iterator = engine_list_head;
		}
	return;
	}
