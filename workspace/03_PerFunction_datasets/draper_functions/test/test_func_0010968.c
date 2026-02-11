g_opendir(Char *str, glob_t *pglob)
{
	char buf[MAXPATHLEN];

	if (!*str) {
		my_strlcpy(buf, ".", sizeof(buf));
	} else {
		if (g_Ctoc(str, buf, sizeof(buf)))
			return(NULL);
	}

	if (pglob->gl_flags & GLOB_ALTDIRFUNC)
		return((DIR*)(*pglob->gl_opendir)(buf));

	return(PerlDir_open(buf));
}
