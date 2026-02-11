callsystem_argv_dup(const char * argv[], char **argv_dup[])
{
	size_t sz;
	int i;

	if(!argv)
	{
		*argv_dup =(char**)0;
		return 0;
	}

	sz = veczsize((char***)&argv);
	*argv_dup = malloc(sz * sizeof(char*));

	if(!*argv_dup)
	{
		return -1;
	}

	for(i=0 ; i<sz ; i++)
	{
		if(argv[i])
		{
			(*argv_dup)[i] = strdup(argv[i]);
			if(!(*argv_dup)[i])
			{
				return -1;
			}
		}
		else
			(*argv_dup)[i] =(char*)0;
	}
	return 0;
}
