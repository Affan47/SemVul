parse_set_misc_enabled(char *p, int *vp)
{
	gfarm_error_t e;
	char *s;
	int v;

	e = get_one_argument(p, &s);
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1000969,
			"get_one_argument failed "
			"when parsing misc enabled (%s): %s",
			p, gfarm_error_string(e));
		return (e);
	}

	if (*vp != MISC_DEFAULT)
		return (GFARM_ERR_NO_ERROR);
	if (strcmp(s, "enable") == 0)
		v = 1;
	else if (strcmp(s, "disable") == 0)
		v = 0;
	else {
		gflog_debug(GFARM_MSG_1000970,
			"'enable' or 'disable' expected "
			"when parsing misc enabled but (%s)",
			s);
		return (GFARM_ERRMSG_ENABLED_OR_DISABLED_EXPECTED);
	}
	*vp = v;
	return (GFARM_ERR_NO_ERROR);
}
