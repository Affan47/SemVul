userfile(void)
{
	static char File[LONG_STRING_SIZE] = "";


	if (*File == '\0')
	{
		sprintf(File,"%s%c%s",confdir(),C_SLASH,USERFILE);

		if (*File == '\0')
		{
			print_msg(PRT_ERR,"%s\n","Invalid filename for user access!");
			Exit(23);
		}
	}

	return File;
}
