audit_rule_setup(char *opt, int *filter, int *act, int lineno)
{
	int rc;
	char *p;

	if (++multiple != 1)
		return 3;

	p = strchr(opt, ',');
	if (p == NULL || strchr(p+1, ','))
		return 2;
	*p = 0;


	if (lookup_filter(opt, filter) == 2) {
		rc = lookup_action(opt, act);
		if (rc != 0) {
			*p = ',';
			return rc;
		}
	}


	*p = ',';
	opt = p+1;


	if (*filter == AUDIT_FILTER_UNSET)
		lookup_filter(opt, filter);
	else {
		rc = lookup_action(opt, act);
		if (rc != 0)
			return rc;
	}


	if (*filter == AUDIT_FILTER_UNSET || *act == -1)
		return 2;


	if (*filter == AUDIT_FILTER_ENTRY) {
		*filter = AUDIT_FILTER_EXIT;
		fprintf(stderr,
		    "Warning - entry rules deprecated, changing to exit rule");
		if (lineno)
			fprintf(stderr, " in line %d", lineno);
		fprintf(stderr, "\n");
	}

	return 0;
}
