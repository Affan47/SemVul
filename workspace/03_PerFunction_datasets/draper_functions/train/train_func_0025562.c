GenerateOutputControlFileName(char * pchFontFile, char * pchOutputFont)
{
	char * pchIn = pchFontFile;
	while (*pchIn != 0)
		pchIn++;

	while (*pchIn != '\\' && *pchIn != ':' && pchIn >= pchFontFile)
		pchIn--;
	pchIn++;

	char * pchOut = pchOutputFont;
	while (*pchIn != '.' && *pchIn != 0)
	{
		*pchOut++ = *pchIn++;
	}

	*pchOut++ = '.';
	*pchOut++ = 'g';
	*pchOut++ = 't';
	*pchOut++ = 'f';
	*pchOut = 0;
}
