remove_spaces(char *src)
{
	char *ptr=src;
	while (*ptr != 0)
	{
		if(*ptr == ' ')
			*ptr = '_';
		ptr++;
	}
}
