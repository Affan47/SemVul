parse_whitespace_rule(const char *string)
{
	unsigned rule = WS_DEFAULT_RULE;

	while (string) {
		int i;
		size_t len;
		const char *ep;
		int negated = 0;

		string = string + strspn(string, ", \t\n\r");
		ep = strchr(string, ',');
		if (!ep)
			len = strlen(string);
		else
			len = ep - string;

		if (*string == '-') {
			negated = 1;
			string++;
			len--;
		}
		if (!len)
			break;
		for (i = 0; i < ARRAY_SIZE(whitespace_rule_names); i++) {
			if (strncmp(whitespace_rule_names[i].rule_name,
				    string, len))
				continue;
			if (negated)
				rule &= ~whitespace_rule_names[i].rule_bits;
			else
				rule |= whitespace_rule_names[i].rule_bits;
			break;
		}
		string = ep;
	}
	return rule;
}
