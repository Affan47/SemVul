add_additional_variables(char *name, bool insert)
{
	struct cursor *ptr;
	struct arguments *p;
	int (* strcmp_fn)(const char *, const char *) = ((name[0] == ':' || name[0] == '"') ? strcmp : pg_strcasecmp);

	for (ptr = cur; ptr != NULL; ptr=ptr->next)
	{
		if (strcmp_fn(ptr->name, name) == 0)
			break;
	}

	if (ptr == NULL)
	{
		mmerror(PARSE_ERROR, ET_ERROR, "cursor \"%s\" does not exist", name);
		return NULL;
	}

	if (insert)
	{


		for (p = (SAMEFUNC(ptr) ? ptr->argsinsert : ptr->argsinsert_oos); p; p = p->next)
			add_variable_to_tail(&argsinsert, p->variable, p->indicator);
	}


	for (p = (SAMEFUNC(ptr) ? ptr->argsresult : ptr->argsresult_oos); p; p = p->next)
		add_variable_to_tail(&argsresult, p->variable, p->indicator);

	return ptr;
}
