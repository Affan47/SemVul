shorten_unambiguous_ref(const char *ref, int strict)
{
	int i;
	static char **scanf_fmts;
	static int nr_rules;
	char *short_name;


	if (!nr_rules) {
		size_t total_len = 0;


		for (; ref_rev_parse_rules[nr_rules]; nr_rules++)

			total_len += strlen(ref_rev_parse_rules[nr_rules]);

		scanf_fmts = xmalloc(nr_rules * sizeof(char *) + total_len);

		total_len = 0;
		for (i = 0; i < nr_rules; i++) {
			scanf_fmts[i] = (char *)&scanf_fmts[nr_rules]
					+ total_len;
			gen_scanf_fmt(scanf_fmts[i], ref_rev_parse_rules[i]);
			total_len += strlen(ref_rev_parse_rules[i]);
		}
	}


	if (!nr_rules)
		return xstrdup(ref);


	short_name = xstrdup(ref);


	for (i = nr_rules - 1; i > 0 ; --i) {
		int j;
		int rules_to_fail = i;
		int short_name_len;

		if (1 != sscanf(ref, scanf_fmts[i], short_name))
			continue;

		short_name_len = strlen(short_name);


		if (strict)
			rules_to_fail = nr_rules;


		for (j = 0; j < rules_to_fail; j++) {
			const char *rule = ref_rev_parse_rules[j];
			unsigned char short_objectname[20];
			char refname[PATH_MAX];


			if (i == j)
				continue;


			mksnpath(refname, sizeof(refname),
				 rule, short_name_len, short_name);
			if (!read_ref(refname, short_objectname))
				break;
		}


		if (j == rules_to_fail)
			return short_name;
	}

	free(short_name);
	return xstrdup(ref);
}
