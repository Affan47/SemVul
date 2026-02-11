parseLet (const unsigned char *line)
{
	vString *name = vStringNew ();


	const unsigned char *cp = line + 3;
	const unsigned char *np = line;

	if (isspace ((int) *cp))
	{
		while (*cp && isspace ((int) *cp))
			++cp;


		if (!*cp || *cp == '&' || *cp == '@' || *cp == '[' )
			goto cleanUp;


		np = cp;
		++np;
		if ((int) *cp == 'v' && (int) *np == ':' )
			goto cleanUp;


		while (*cp && *cp != '$' && !isalnum ((int) *cp))
			++cp;

		if (!*cp)
			goto cleanUp;


		do
		{
			if (!*cp)
				break;

			vStringPut (name, (int) *cp);
			++cp;
		} while (isalnum ((int) *cp)  ||  *cp == '_'  ||  *cp == '#'  ||  *cp == ':'  ||  *cp == '$');
		vStringTerminate (name);
		makeSimpleTag (name, VimKinds, K_VARIABLE);
		vStringClear (name);
	}

cleanUp:
	vStringDelete (name);
}
