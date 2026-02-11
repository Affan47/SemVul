findRestTags (void)
{
	vString *name = vStringNew ();
	const unsigned char *line;

	memset(kindchars, 0, sizeof kindchars);
	nestingLevels = nestingLevelsNew();

	while ((line = fileReadLine ()) != NULL)
	{
		int line_len = strlen((const char*) line);
		int name_len_bytes = vStringLength(name);
		int name_len = utf8_strlen(vStringValue(name), name_len_bytes);


		if (name_len < 0)
			name_len = name_len_bytes;


		if (line_len >= name_len && name_len > 0 &&
			ispunct(line[0]) && issame((const char*) line))
		{
			char c = line[0];
			int kind = get_kind(c);

			if (kind >= 0)
			{
				makeRestTag(name, kind);
				continue;
			}
		}
		vStringClear (name);
		if (! isspace(*line))
			vStringCatS(name, (const char*) line);
		vStringTerminate(name);
	}
	vStringDelete (name);
	nestingLevelsFree(nestingLevels);
}
