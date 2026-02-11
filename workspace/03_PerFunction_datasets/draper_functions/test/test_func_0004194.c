parse_grep(const char *str)
{
	int	len;
	char	*cp = (char *)str, *cp2;


	if (*cp != '|')
		return;
	cp++;
	while (isspace(*cp))
		cp++;
	if (strncmp(cp, "grep ", 5)) {
		kdb_printf("invalid 'pipe', see grephelp\n");
		return;
	}
	cp += 5;
	while (isspace(*cp))
		cp++;
	cp2 = strchr(cp, '\n');
	if (cp2)
		*cp2 = '\0';
	len = strlen(cp);
	if (len == 0) {
		kdb_printf("invalid 'pipe', see grephelp\n");
		return;
	}

	if (*cp == '"') {


		cp++;
		cp2 = strchr(cp, '"');
		if (!cp2) {
			kdb_printf("invalid quoted string, see grephelp\n");
			return;
		}
		*cp2 = '\0';
	}
	kdb_grep_leading = 0;
	if (*cp == '^') {
		kdb_grep_leading = 1;
		cp++;
	}
	len = strlen(cp);
	kdb_grep_trailing = 0;
	if (*(cp+len-1) == '$') {
		kdb_grep_trailing = 1;
		*(cp+len-1) = '\0';
	}
	len = strlen(cp);
	if (!len)
		return;
	if (len >= KDB_GREP_STRLEN) {
		kdb_printf("search string too long\n");
		return;
	}
	strcpy(kdb_grep_string, cp);
	kdb_grepping_flag++;
	return;
}
