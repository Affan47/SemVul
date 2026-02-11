replace_auto_config_value(ConfigVariable **head_p, ConfigVariable **tail_p,
						  const char *name, const char *value)
{
	ConfigVariable *item,
			   *prev = NULL;


	for (item = *head_p; item != NULL; item = item->next)
	{
		if (strcmp(item->name, name) == 0)
		{

			pfree(item->value);
			if (value != NULL)
			{

				item->value = pstrdup(value);
			}
			else
			{

				if (*head_p == item)
					*head_p = item->next;
				else
					prev->next = item->next;
				if (*tail_p == item)
					*tail_p = prev;

				pfree(item->name);
				pfree(item->filename);
				pfree(item);
			}
			return;
		}
		prev = item;
	}


	if (value == NULL)
		return;


	item = palloc(sizeof *item);
	item->name = pstrdup(name);
	item->value = pstrdup(value);
	item->errmsg = NULL;
	item->filename = pstrdup("");
	item->sourceline = 0;
	item->ignore = false;
	item->applied = false;
	item->next = NULL;

	if (*head_p == NULL)
		*head_p = item;
	else
		(*tail_p)->next = item;
	*tail_p = item;
}
