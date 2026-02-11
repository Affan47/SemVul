go_regcomp (GORegexp *gor, const char *pat, int cflags)
{
	GError *error = NULL;
	GRegex *r;
	int coptions =
		((cflags & GO_REG_ICASE) ? G_REGEX_CASELESS : 0) |
		((cflags & GO_REG_NEWLINE) ? G_REGEX_MULTILINE : 0);

	gor->ppcre = r = g_regex_new (pat, coptions, 0, &error);

	if (r == NULL) {

		switch (error->code) {
		case G_REGEX_ERROR_STRAY_BACKSLASH:
		case G_REGEX_ERROR_MISSING_CONTROL_CHAR:
		case G_REGEX_ERROR_UNRECOGNIZED_ESCAPE:

			return GO_REG_EESCAPE;
		case G_REGEX_ERROR_QUANTIFIERS_OUT_OF_ORDER:
		case G_REGEX_ERROR_QUANTIFIER_TOO_BIG:
			return GO_REG_EBRACE;
		case G_REGEX_ERROR_UNTERMINATED_CHARACTER_CLASS:
			return GO_REG_EBRACK;
		case G_REGEX_ERROR_INVALID_ESCAPE_IN_CHARACTER_CLASS:
		case G_REGEX_ERROR_UNKNOWN_POSIX_CLASS_NAME:
			return GO_REG_ECTYPE;
		case G_REGEX_ERROR_RANGE_OUT_OF_ORDER:
			return GO_REG_ERANGE;
		case G_REGEX_ERROR_NOTHING_TO_REPEAT:

			return GO_REG_BADRPT;
		case G_REGEX_ERROR_UNMATCHED_PARENTHESIS:
		case G_REGEX_ERROR_UNTERMINATED_COMMENT:

			return GO_REG_EPAREN;
		case G_REGEX_ERROR_INEXISTENT_SUBPATTERN_REFERENCE:
			return GO_REG_ESUBREG;
		case G_REGEX_ERROR_EXPRESSION_TOO_LARGE:

			return GO_REG_ESIZE;
		case G_REGEX_ERROR_MEMORY_ERROR:
			return GO_REG_ESPACE;
		default:
			return GO_REG_BADPAT;
		}
	} else {
		gor->re_nsub = g_regex_get_capture_count (r);
		gor->nosub = (cflags & GO_REG_NOSUB) != 0;
		return 0;
	}
	return 0;
}
