valid_wild_card_simple(const char *data)
{
	const char *p;
	char tmpch;
	int nonwild = 0;
	int wild = 0;


	p = data;

	while((tmpch = *p++))
	{


		if(tmpch == '\\' && *p)
		{
			p++;
			if(++nonwild >= ConfigFileEntry.min_nonwildcard_simple)
				return 1;
		}
		else if(!IsMWildChar(tmpch))
		{

			if(++nonwild >= ConfigFileEntry.min_nonwildcard_simple)
				return 1;
		}
		else
			wild++;
	}


	return wild == 0;
}
