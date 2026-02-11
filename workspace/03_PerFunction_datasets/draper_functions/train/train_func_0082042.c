xregcomp(regex_t *preg, const char *regex, int cflags)
{
	char *errmsg = regcomp_or_errmsg(preg, regex, cflags);
	if (errmsg) {
		bb_error_msg_and_die("bad regex '%s': %s", regex, errmsg);
	}
}
