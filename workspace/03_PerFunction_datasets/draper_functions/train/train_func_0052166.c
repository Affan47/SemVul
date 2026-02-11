RebuildStringTables(void)
{
	UINT32	storageNeeded, i;
	char	* traverse;

	storageNeeded =				(menuStrings.mainStringLength + menuStrings.subStringLength) * menuStrings.numStrings;

	menuStrings.mainList =		(const char **)	realloc((char *)	menuStrings.mainList,		sizeof(char *) * menuStrings.length);
	menuStrings.subList =		(const char **)	realloc((char *)	menuStrings.subList,		sizeof(char *) * menuStrings.length);
	menuStrings.flagList =						realloc(			menuStrings.flagList,		sizeof(char)   * menuStrings.length);
	menuStrings.mainStrings =					realloc(			menuStrings.mainStrings,	sizeof(char *) * menuStrings.numStrings);
	menuStrings.subStrings =					realloc(			menuStrings.subStrings,		sizeof(char *) * menuStrings.numStrings);
	menuStrings.buf =							realloc(			menuStrings.buf,			sizeof(char)   * storageNeeded);

	if(	(!menuStrings.mainList && menuStrings.length) ||
		(!menuStrings.subList && menuStrings.length) ||
		(!menuStrings.flagList && menuStrings.length) ||
		(!menuStrings.mainStrings && menuStrings.numStrings) ||
		(!menuStrings.subStrings && menuStrings.numStrings) ||
		(!menuStrings.buf && storageNeeded))
	{
		logerror(	"cheat: memory allocation error\n"
					"	length =			%.8X\n"
					"	numStrings =		%.8X\n"
					"	mainStringLength =	%.8X\n"
					"	subStringLength =	%.8X\n"
					"%.8X %.8X %.8X %.8X %.8X %.8X\n",
					menuStrings.length,
					menuStrings.numStrings,
					menuStrings.mainStringLength,
					menuStrings.subStringLength,

					(int)menuStrings.mainList,
					(int)menuStrings.subList,
					(int)menuStrings.flagList,
					(int)menuStrings.mainStrings,
					(int)menuStrings.subStrings,
					(int)menuStrings.buf);

		exit(1);
	}

	traverse = menuStrings.buf;

	for(i = 0; i < menuStrings.numStrings; i++)
	{
		menuStrings.mainStrings[i] = traverse;
		traverse += menuStrings.mainStringLength;

		menuStrings.subStrings[i] = traverse;
		traverse += menuStrings.subStringLength;
	}
}
