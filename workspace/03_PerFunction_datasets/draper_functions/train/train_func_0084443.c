required_string_fred(char *pstr, char *end)
{
	char *backup = Mp;

	token_found = pstr;
	if (fred_parse_flag)
		return 0;

	ignore_white_space();
	while (*Mp != EOF_CHAR && strnicmp(pstr, Mp, strlen(pstr))) {
		if ((*Mp == '#') || (end && !strnicmp(end, Mp, strlen(end)))) {
			Mp = NULL;
			break;
		}

		advance_to_eoln(NULL);
		ignore_white_space();
	}

	if (!Mp || (*Mp == EOF_CHAR)) {
		diag_printf("Required string [%s] not found\n", pstr);
		Mp = backup;
		Token_found_flag = 0;
		return 0;
	}

	Mp += strlen(pstr);
	diag_printf("Found required string [%s]\n", pstr);
	Token_found_flag = 1;
	return 1;
}
