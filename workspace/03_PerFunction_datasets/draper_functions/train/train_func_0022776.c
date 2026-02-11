ExpandOptionName(const char * name, int depth)
{
	ARGS	args;
	char	upName[MAX_MACRO_LEN + 2];

	if (depth > MAX_OPTION_DEPTH)
	{
		fprintf(stderr, "Too many levels of option macros\n");

		return FALSE;
	}

	if (strlen(name) > MAX_MACRO_LEN)
	{
		fprintf(stderr, "Macro name \"%c%s\" is too long\n",
			*name + 'A' - 'a', name + 1);

		return FALSE;
	}


	if ((depth == 0) && isLower(*name))
	{
		strcpy(upName, name);

		upName[0] += 'A' - 'a';

		name = upName;
	}

	if (isLower(*name))
	{
		fprintf(stderr, "Option macro \"%s\" must be upper case\n",
			name);

		return FALSE;
	}

	if (!isMacro(*name))
	{
		fprintf(stderr, "String value \"%s\" is not a macro name\n",
			name);

		return FALSE;
	}

	if (!ExpandMacro(MACRO_TYPE_OPTION, name, &args))
		return FALSE;

	return ParseOptions(&args, depth + 1);
}
