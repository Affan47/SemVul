rc_fieldcpy (char *string, char **uptr)
{
	char           *ptr;

	ptr = *uptr;
	if (*ptr == '"')
	{
		ptr++;
		while (*ptr != '"' && *ptr != '\0' && *ptr != '\n')
		{
			*string++ = *ptr++;
		}
		*string = '\0';
		if (*ptr == '"')
		{
			ptr++;
		}
		*uptr = ptr;
		return;
	}

	while (*ptr != ' ' && *ptr != '\t' && *ptr != '\0' && *ptr != '\n' &&
			*ptr != '=' && *ptr != ',')
	{
		*string++ = *ptr++;
	}
	*string = '\0';
	*uptr = ptr;
	return;
}
