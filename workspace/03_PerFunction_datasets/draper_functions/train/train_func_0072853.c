opt_test_parse_option(char *namebuff, char *valbuff, char *str)
{
	char *basestr, *sepstr;
	basestr = str;
	sepstr = 0;
	while (*str)
	{
		if (*str == ' ')
			continue;
		if (*str == ':')
			sepstr = str;
		if (*str == ',')
			break;
		str++;
	}

	if (!sepstr)
		sepstr = str;

	memcpy(namebuff,basestr,sepstr-basestr);
	namebuff[sepstr-basestr] = 0;

	if (sepstr != str)
	{
		memcpy(valbuff,sepstr+1,str-sepstr-1);
		valbuff[str-sepstr-1] = 0;
	}
	else
		*valbuff = 0;


	if (*str)
		str++;

	return str;
}
