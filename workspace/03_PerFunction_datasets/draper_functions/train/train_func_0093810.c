assign_custom_variable_classes(const char *newval, bool doit, GucSource source)
{


	bool		hasSpaceAfterToken = false;
	const char *cp = newval;
	int			symLen = 0;
	char		c;
	StringInfoData buf;

	initStringInfo(&buf);
	while ((c = *cp++) != '\0')
	{
		if (isspace((unsigned char) c))
		{
			if (symLen > 0)
				hasSpaceAfterToken = true;
			continue;
		}

		if (c == ',')
		{
			if (symLen > 0)
			{
				appendStringInfoChar(&buf, ',');
				symLen = 0;
			}
			hasSpaceAfterToken = false;
			continue;
		}

		if (hasSpaceAfterToken || !(isalnum((unsigned char) c) || c == '_'))
		{


			pfree(buf.data);
			return NULL;
		}
		appendStringInfoChar(&buf, c);
		symLen++;
	}


	if (symLen == 0 && buf.len > 0)
		buf.data[--buf.len] = '\0';


	newval = guc_strdup(LOG, buf.data);

	pfree(buf.data);
	return newval;
}
