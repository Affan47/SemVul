set_pattern(info, pattern, search_type)
	struct pattern_info *info;
	char *pattern;
	int search_type;
{
	if (pattern == NULL)
		CLEAR_PATTERN(search_info.compiled);
	else if (compile_pattern(pattern, search_type, &info->compiled) < 0)
		return -1;

	if (info->text != NULL)
		free(info->text);
	info->text = NULL;
	if (pattern != NULL)
	{
		info->text = (char *) ecalloc(1, strlen(pattern)+1);
		strcpy(info->text, pattern);
	}
	info->search_type = search_type;


	is_ucase_pattern = is_ucase(pattern);
	if (is_ucase_pattern && caseless != OPT_ONPLUS)
		is_caseless = 0;
	else
		is_caseless = caseless;
	return 0;
}
