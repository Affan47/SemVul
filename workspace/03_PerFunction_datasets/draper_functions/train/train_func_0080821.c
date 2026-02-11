_make_info_table (driver_list **head, int *driver_count)
{
	driver_list *list;
	int i;
	ao_info **table;
	driver_list **drivers_table;

	*driver_count = 0;


	list = *head;
	i = 0;
	while (list != NULL) {
		i++;
		list = list->next;
	}


	drivers_table = (driver_list **) calloc(i, sizeof(driver_list *));
	if (drivers_table == NULL)
		return (ao_info **) NULL;
	list = *head;
	*driver_count = i;
	for (i = 0; i < *driver_count; i++, list = list->next)
		drivers_table[i] = list;
	qsort(drivers_table, i, sizeof(driver_list *),
			(int(*)(const void *, const void *))
			_compar_driver_priority);
	*head = drivers_table[0];
	for (i = 1; i < *driver_count; i++)
		drivers_table[i-1]->next = drivers_table[i];
	drivers_table[i-1]->next = NULL;


	table = (ao_info **) calloc(i, sizeof(ao_info *));
	if (table != NULL) {
		for (i = 0; i < *driver_count; i++)
			table[i] = drivers_table[i]->functions->driver_info();
	}

	free(drivers_table);

	return table;
}
