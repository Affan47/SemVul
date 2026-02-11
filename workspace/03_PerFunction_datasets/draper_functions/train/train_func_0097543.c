check_wild_gline(const char *user, const char *host)
{
	const char *p;
	char tmpch;
	int nonwild;

	nonwild = 0;
	p = user;

	while((tmpch = *p++))
	{
		if(!IsKWildChar(tmpch))
		{

			if(++nonwild >= ConfigFileEntry.min_nonwildcard)
				break;
		}
	}

	if(nonwild < ConfigFileEntry.min_nonwildcard)
	{

		p = host;
		while((tmpch = *p++))
		{
			if(!IsKWildChar(tmpch))
				if(++nonwild >= ConfigFileEntry.min_nonwildcard)
					break;
		}
	}

	if(nonwild < ConfigFileEntry.min_nonwildcard)
		return 1;
	else
		return 0;
}
