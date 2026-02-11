parse_icmp(const char *icmptype, uint8_t *type, uint8_t code[])
{
	static const unsigned int limit = ARRAY_SIZE(icmp_codes);
	unsigned int match = limit;
	unsigned int i;

	for (i = 0; i < limit; i++) {
		if (strncasecmp(icmp_codes[i].name, icmptype, strlen(icmptype))
		    == 0) {
			if (match != limit)
				xtables_error(PARAMETER_PROBLEM,
					   "Ambiguous ICMP type `%s':"
					   " `%s' or `%s'?",
					   icmptype,
					   icmp_codes[match].name,
					   icmp_codes[i].name);
			match = i;
		}
	}

	if (match != limit) {
		*type = icmp_codes[match].type;
		code[0] = icmp_codes[match].code_min;
		code[1] = icmp_codes[match].code_max;
	} else {
		char *slash;
		char buffer[strlen(icmptype) + 1];
		unsigned int number;

		strcpy(buffer, icmptype);
		slash = strchr(buffer, '/');

		if (slash)
			*slash = '\0';

		if (!xtables_strtoui(buffer, NULL, &number, 0, UINT8_MAX))
			xtables_error(PARAMETER_PROBLEM,
				   "Invalid ICMP type `%s'\n", buffer);
		*type = number;
		if (slash) {
			if (!xtables_strtoui(slash+1, NULL, &number, 0, UINT8_MAX))
				xtables_error(PARAMETER_PROBLEM,
					   "Invalid ICMP code `%s'\n",
					   slash+1);
			code[0] = code[1] = number;
		} else {
			code[0] = 0;
			code[1] = 0xFF;
		}
	}
}
