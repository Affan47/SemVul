addExtensionList (
		stringList *const slist, const char *const elist, const boolean clear)
{
	char *const extensionList = eStrdup (elist);
	const char *extension = NULL;
	boolean first = TRUE;

	if (clear)
	{
		verbose ("      clearing\n");
		stringListClear (slist);
	}
	verbose ("      adding: ");
	if (elist != NULL  &&  *elist != '\0')
	{
		extension = extensionList;
		if (elist [0] == EXTENSION_SEPARATOR)
			++extension;
	}
	while (extension != NULL)
	{
		char *separator = strchr (extension, EXTENSION_SEPARATOR);
		if (separator != NULL)
			*separator = '\0';
		verbose ("%s%s", first ? "" : ", ",
				*extension == '\0' ? "(NONE)" : extension);
		stringListAdd (slist, vStringNewInit (extension));
		first = FALSE;
		if (separator == NULL)
			extension = NULL;
		else
			extension = separator + 1;
	}
	if (Option.verbose)
	{
		printf ("\n      now: ");
		stringListPrint (slist);
		putchar ('\n');
	}
	eFree (extensionList);
}
