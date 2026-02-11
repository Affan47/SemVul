READ_get_pattern(PATTERN *pattern)
{
	int type = PATTERN_type(*pattern);
	int index = PATTERN_index(*pattern);
	const char *str;
	const char *before = _no_quote ? "" : "'";
	const char *after = _no_quote ? "" : "'";

	switch(type)
	{
		case RT_RESERVED:

			str = COMP_res_info[index].name;
			if (ispunct((unsigned char)*str))
				snprintf(_buffer, BUF_MAX, "%s%s%s", before, str, after);
			else
				strcpy(_buffer, str);
			break;

		case RT_NUMBER:
		case RT_IDENTIFIER:
		case RT_CLASS:
			snprintf(_buffer, BUF_MAX, "%s%s%s", before, TABLE_get_symbol_name(EVAL->table, index), after);
			break;

		case RT_STRING:
		case RT_TSTRING:
			if (_no_quote)
				snprintf(_buffer, BUF_MAX, "\"%s\"", TABLE_get_symbol_name(EVAL->string, index));
			else
				strcpy(_buffer, "string");
			break;

		case RT_NEWLINE:
		case RT_END:
			strcpy(_buffer, "end of expression");
			break;

		case RT_SUBR:

			strcpy(_buffer, COMP_subr_info[index].name);
			break;

		case RT_COMMENT:
			strncpy(_buffer, TABLE_get_symbol_name(EVAL->string, index), BUF_MAX);
			_buffer[BUF_MAX] = 0;
			break;

		default:
			sprintf(_buffer, "%s?%08X?%s", before, *pattern, after);
	}

	return _buffer;
}
