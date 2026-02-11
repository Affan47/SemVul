load_hba(void)
{
	FILE	   *file;
	List	   *hba_lines = NIL;
	List	   *hba_line_nums = NIL;
	List	   *hba_raw_lines = NIL;
	ListCell   *line,
			   *line_num,
			   *raw_line;
	List	   *new_parsed_lines = NIL;
	bool		ok = true;
	MemoryContext linecxt;
	MemoryContext oldcxt;
	MemoryContext hbacxt;

	file = AllocateFile(HbaFileName, "r");
	if (file == NULL)
	{
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not open configuration file \"%s\": %m",
						HbaFileName)));
		return false;
	}

	linecxt = tokenize_file(HbaFileName, file, &hba_lines, &hba_line_nums, &hba_raw_lines);
	FreeFile(file);


	Assert(PostmasterContext);
	hbacxt = AllocSetContextCreate(PostmasterContext,
								   "hba parser context",
								   ALLOCSET_DEFAULT_MINSIZE,
								   ALLOCSET_DEFAULT_MINSIZE,
								   ALLOCSET_DEFAULT_MAXSIZE);
	oldcxt = MemoryContextSwitchTo(hbacxt);
	forthree(line, hba_lines, line_num, hba_line_nums, raw_line, hba_raw_lines)
	{
		HbaLine    *newline;

		if ((newline = parse_hba_line(lfirst(line), lfirst_int(line_num), lfirst(raw_line))) == NULL)
		{


			MemoryContextReset(hbacxt);
			new_parsed_lines = NIL;
			ok = false;


			continue;
		}

		new_parsed_lines = lappend(new_parsed_lines, newline);
	}


	if (ok && new_parsed_lines == NIL)
	{
		ereport(LOG,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("configuration file \"%s\" contains no entries",
						HbaFileName)));
		ok = false;
	}


	MemoryContextDelete(linecxt);
	MemoryContextSwitchTo(oldcxt);

	if (!ok)
	{

		MemoryContextDelete(hbacxt);
		return false;
	}


	if (parsed_hba_context != NULL)
		MemoryContextDelete(parsed_hba_context);
	parsed_hba_context = hbacxt;
	parsed_hba_lines = new_parsed_lines;

	return true;
}
