next_insert(char *text)
{
	char	   *ptr = text;
	bool		string = false;

	for (; *ptr != '\0' && (*ptr != '?' || string); ptr++)
	{
		if (*ptr == '\\')
			ptr++;
		else if (*ptr == '\'')
			string = string ? false : true;
	}

	return (*ptr == '\0') ? NULL : ptr;
}
