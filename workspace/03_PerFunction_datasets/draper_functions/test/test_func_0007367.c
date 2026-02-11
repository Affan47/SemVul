session_localvar_find(session_t *s, const char *key) {
	session_param_t *pl;

	if (!s)
		return NULL;

	for (pl = s->local_vars; pl; pl = pl->next) {
		session_param_t *v = pl;
		if (!xstrcmp(v->key, key))
			return v;
	}

	return NULL;
}
