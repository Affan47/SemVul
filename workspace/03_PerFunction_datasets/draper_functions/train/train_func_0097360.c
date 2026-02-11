json_find(json *j, const char *name)
{
	while (j && name)
	{
		if (j->name)
		{
			if (!strcmp(name, j->name))
				return j;
		}

		j = j->next;
	}

	return NULL;
}
