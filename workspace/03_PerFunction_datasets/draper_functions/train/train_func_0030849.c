json_close(json *j)
{
	if (!j)
		return;

	while (j)
	{
		json *save = j;
		j = j->next;

		if ((save->type == type_object) || (save->type == type_array))
			json_close(save->head);
		else if ((save->type == type_string) && save->str)
			free(save->str);

		if (save->name)
			free(save->name);

		free(save);
	}
}
