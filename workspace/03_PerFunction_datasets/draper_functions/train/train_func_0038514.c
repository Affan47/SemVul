function_resolve(name)
	 char          *name;
{
	char           *full_name;
	char			core_name[84];
	int				index;

	struct function_type *pointer = function_table;

	if (function_table == NULL)
		return (NULL);


	index = 0;

	while (*name && index < 80) {
		if (*name == '<') {
			break;
		} else {
			core_name[index++] = *name++;
		}
	}
	core_name[index] = 0;


	full_name = (char *) expand_function(core_name);


	do {
		if (!strcmp(full_name, pointer->name))
			return (pointer);
		else
			pointer = pointer->next_function;
	}
	while (pointer != NULL);


	return (NULL);
}
