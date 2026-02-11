load_libraries(const char *libraries, const char *gucname, bool restricted)
{
	char	   *rawstring;
	List	   *elemlist;
	ListCell   *l;

	if (libraries == NULL || libraries[0] == '\0')
		return;


	rawstring = pstrdup(libraries);


	if (!SplitIdentifierString(rawstring, ',', &elemlist))
	{

		pfree(rawstring);
		list_free(elemlist);
		ereport(LOG,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("invalid list syntax in parameter \"%s\"",
						gucname)));
		return;
	}

	foreach(l, elemlist)
	{
		char	   *tok = (char *) lfirst(l);
		char	   *filename;

		filename = pstrdup(tok);
		canonicalize_path(filename);

		if (restricted && first_dir_separator(filename) == NULL)
		{
			char	   *expanded;

			expanded = palloc(strlen("$libdir/plugins/") + strlen(filename) + 1);
			strcpy(expanded, "$libdir/plugins/");
			strcat(expanded, filename);
			pfree(filename);
			filename = expanded;
		}
		load_file(filename, restricted);
		ereport(LOG,
				(errmsg("loaded library \"%s\"", filename)));
		pfree(filename);
	}

	pfree(rawstring);
	list_free(elemlist);
}
