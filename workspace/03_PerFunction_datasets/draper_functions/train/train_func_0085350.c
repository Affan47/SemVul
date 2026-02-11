factory_type_store_remove(struct factory_type *ft)
{
	int i;
	int found_it = 0;

	for (i = 0; i < number_of_types; i++)
	{
		if (!found_it)
		{
			if (factory_type_store[i] == ft)
			{
				found_it = 1;
			}
		}
		else
		{
			factory_type_store[i-1] = factory_type_store[i];
		}
	}

	if (found_it)
	{
		factory_type_store[i-1] = NULL;
		number_of_types--;
	}
}
