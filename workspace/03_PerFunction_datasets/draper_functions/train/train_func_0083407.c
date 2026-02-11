parse_stringlist(char *p, char **op,
	gfarm_stringlist *list, const char *listname)
{
	gfarm_error_t e;
	char *tmp, *arg;

	e = gfarm_strtoken(&p, &arg);
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1002448,
		    "parsing argument %s of %s failed: %s",
		    p, listname, gfarm_error_string(e));
		return (e);
	}
	if (arg == NULL) {
		gflog_debug(GFARM_MSG_1002449,
		    "missing argument for %s", listname);
		return (GFARM_ERRMSG_MISSING_USER_MAP_FILE_ARGUMENT);
	}
	e = gfarm_strtoken(&p, &tmp);
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1002450,
		    "parsing argument %s of %s failed: %s",
		    p, listname, gfarm_error_string(e));
		return (e);
	}
	if (tmp != NULL) {
		gflog_debug(GFARM_MSG_1002451,
		    "Too many arguments for %s", listname);
		return (GFARM_ERRMSG_TOO_MANY_ARGUMENTS);
	}
	arg = strdup(arg);
	if (arg == NULL) {
		gflog_debug(GFARM_MSG_1002452,
		    "failed to allocate an argument of %s: no memory",
		    listname);
		return (GFARM_ERR_NO_MEMORY);
	}
	e = gfarm_stringlist_add(list, arg);
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1002453,
		    "failed to allocate a %s entry for \"%s\": no memory",
		    listname, arg);
		free(arg);
	}
	return (e);
}
