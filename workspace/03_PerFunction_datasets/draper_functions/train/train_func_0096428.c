gnumeric_search (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	char const *needle = value_peek_string (argv[0]);
	char const *haystack = value_peek_string (argv[1]);
	gnm_float start = argv[2] ? value_get_as_float (argv[2]) : 1.0;
	size_t i, istart;
	char const *hay2;
	GORegexp r;

	if (start < 1 || start >= INT_MAX)
		return value_new_error_VALUE (ei->pos);

	istart = (int)(start - 1);

	for (i = istart, hay2 = haystack; i > 0; i--) {
		if (*hay2 == 0)
			return value_new_error_VALUE (ei->pos);
		hay2 = g_utf8_next_char (hay2);
	}

	if (gnm_regcomp_XL (&r, needle, GO_REG_ICASE, FALSE, FALSE) == GO_REG_OK) {
		GORegmatch rm;

		switch (go_regexec (&r, hay2, 1, &rm, 0)) {
		case GO_REG_NOMATCH:
			break;
		case GO_REG_OK:
			go_regfree (&r);
			return value_new_int
				(1 + istart +
				 g_utf8_pointer_to_offset (hay2, hay2 + rm.rm_so));
		default:
			g_warning ("Unexpected go_regexec result");
		}
		go_regfree (&r);
	} else {
		g_warning ("Unexpected regcomp result");
	}

	return value_new_error_VALUE (ei->pos);
}
