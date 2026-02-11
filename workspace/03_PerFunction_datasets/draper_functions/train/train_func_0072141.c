is_member(const char *user, const char *role)
{
	List	  **line;
	ListCell   *line_item;

	if ((line = get_role_line(user)) == NULL)
		return false;


	if (strcmp(user, role) == 0)
		return true;


	if (list_length(*line) < 4)
		return false;
	for_each_cell(line_item, lnext(lnext(lnext(list_head(*line)))))
	{
		if (strcmp((char *) lfirst(line_item), role) == 0)
			return true;
	}

	return false;
}
