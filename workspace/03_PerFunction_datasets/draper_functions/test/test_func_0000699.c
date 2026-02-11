StrToupper(char *str)
{
	int ii = 0;
	static char retstr[MAXLINE + 1];

	if (str == NULL)
		return NULL;

	for (; ii < strlen(str); ++ii)
		retstr[ii] = ToUpper(str[ii]);

	retstr[ii] = '\0';

	return retstr;
}
