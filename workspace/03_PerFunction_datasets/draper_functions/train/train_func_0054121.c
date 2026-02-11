init_names_txt(ang_file *fp, char *buf)
{
	int i, name_section;
	u32b num_names[RANDNAME_NUM_TYPES];
	char temp[1024];
	int counter = 0;
	error_line = 0;
	memset(num_names, 0, RANDNAME_NUM_TYPES * sizeof(u32b));


	while (file_getl(fp, buf, 1024))
	{
		error_line++;

		if (!buf[0] || '#' == buf[0])
			continue;

		else if ('N' == buf[0])
		{
			if (1 != sscanf(buf, "N:%d", &name_section))
				return PARSE_ERROR_GENERIC;

			if (name_section > RANDNAME_NUM_TYPES)
				return PARSE_ERROR_GENERIC;
		}

		else if ('D' == buf[0])
		{
			num_names[name_section]++;
		}

		else
		{
			return PARSE_ERROR_UNDEFINED_DIRECTIVE;
		}
	}


	file_seek(fp, 0);


	name_sections = C_ZNEW(RANDNAME_NUM_TYPES, cptr*);


	for (i = 0; i < RANDNAME_NUM_TYPES; i++)
	{
		if (num_names[i])
		{
			name_sections[i] = C_ZNEW(num_names[i] + 1, cptr);
		}
	}


	while (file_getl(fp, buf, 1024))
	{
		error_line++;

		if (!buf[0] || '#' == buf[0])
			continue;

		else if ('N' == buf[0])
		{
			if (1 != sscanf(buf, "N:%d", &name_section))
				return PARSE_ERROR_GENERIC;

			if (name_section > RANDNAME_NUM_TYPES)
				return PARSE_ERROR_GENERIC;

			counter = 0;
		}

		else if ('D' == buf[0])
		{
			if (1 != sscanf(buf, "D:%s", temp))
				return PARSE_ERROR_GENERIC;

			name_sections[name_section][counter++] = string_make(temp);
		}

		else
		{
			return PARSE_ERROR_UNDEFINED_DIRECTIVE;
		}
	}


	return 0;
}
