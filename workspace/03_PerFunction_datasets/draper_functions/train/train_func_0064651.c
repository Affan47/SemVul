refname_match(const char *abbrev_name, const char *full_name, const char **rules)
{
	const char **p;
	const int abbrev_name_len = strlen(abbrev_name);

	for (p = rules; *p; p++) {
		if (!strcmp(full_name, mkpath(*p, abbrev_name_len, abbrev_name))) {
			return 1;
		}
	}

	return 0;
}
