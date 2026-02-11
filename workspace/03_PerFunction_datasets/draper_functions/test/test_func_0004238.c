parseFunction (const unsigned char *line)
{
	vString *name = vStringNew ();

	int scope;

	const unsigned char *cp = line + 1;

	if ((int) *++cp == 'n'	&&	(int) *++cp == 'c'	&&
		(int) *++cp == 't'	&&	(int) *++cp == 'i'	&&
		(int) *++cp == 'o'	&&	(int) *++cp == 'n')
			++cp;
	if ((int) *cp == '!')
		++cp;
	if (isspace ((int) *cp))
	{
		while (*cp && isspace ((int) *cp))
			++cp;

		if (*cp)
		{
			cp = skipPrefix (cp, &scope);
			if (isupper ((int) *cp)  ||
					scope == 's'  ||
					scope == '<'  ||
					scope == 'd'  ||
					scope == 'a')
			{
				do
				{
					vStringPut (name, (int) *cp);
					++cp;
				} while (isalnum ((int) *cp) ||  *cp == '_' ||	*cp == '.' ||  *cp == '#');
				vStringTerminate (name);
				makeSimpleTag (name, VimKinds, K_FUNCTION);
				vStringClear (name);
			}
		}
	}


	while ((line = readVimLine ()) != NULL)
	{


		if ( (!strncmp ((const char*) line, "endfo", (size_t) 5) == 0) &&
				(strncmp ((const char*) line, "endf", (size_t) 4) == 0)   )
			break;

	}
	vStringDelete (name);
}
