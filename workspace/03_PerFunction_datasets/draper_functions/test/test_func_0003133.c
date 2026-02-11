session_is_var(session_t *s, const char *key)
{
	const char *intvars[] = { "alias", "descr", "status", "password", "statusdescr", NULL };
	const char **intvar;

	if (!s)
		return -1;


	for (intvar = intvars; *intvar; intvar++)
		if (!xstrcasecmp(key, *intvar))
			return 1;


	return (plugin_var_find(s->plugin, key) != 0);
}
