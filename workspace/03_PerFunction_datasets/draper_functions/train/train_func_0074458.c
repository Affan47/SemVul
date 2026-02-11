append_Old_Info(char *String)
{
	int Cnt = 0;


	if (mcalls < 1)
		return 0;

	if (Old_Info == NULL)
		if ((Old_Info = (char**) calloc(mcalls,sizeof(char*))) == NULL)
			return NO_MEMORY;


	while(Cnt < mcalls && Old_Info[Cnt] != NULL)
		Cnt++;

	if (Cnt == mcalls)
	{
		Cnt = 1;
		free(Old_Info[0]);

		while(Cnt < mcalls)
		{
			Old_Info[Cnt-1] = Old_Info[Cnt];
			Cnt++;
		}

		Cnt = mcalls - 1;
	}

	if ((Old_Info[Cnt] = (char*) calloc(strlen(String)+1,sizeof(char))) == NULL)
		return NO_MEMORY;
	else
		strcpy(Old_Info[Cnt],String);

	return 0;
}
