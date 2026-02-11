wildcard_string_match (const char *key, LookupBisectionCacheItem *bc)
{
	GORegexp rx;
	GORegmatch rm;
	int i, res = LOOKUP_NOT_THERE;


	if (gnm_regcomp_XL (&rx, key, GO_REG_ICASE, TRUE, TRUE) != GO_REG_OK) {
		g_warning ("Unexpected regcomp result");
		return LOOKUP_DATA_ERROR;
	}

	for (i = 0; i < bc->n; i++) {
		if (go_regexec (&rx, bc->data[i].u.str, 1, &rm, 0) == GO_REG_OK) {
			res = bc->data[i].index;
			break;
		}
	}

	go_regfree (&rx);
	return res;
}
