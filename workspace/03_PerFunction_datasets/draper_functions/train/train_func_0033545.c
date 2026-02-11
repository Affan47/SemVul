rc_stringlist_add(RC_STRINGLIST *list, const char *value)
{
	RC_STRING *s = xmalloc(sizeof(*s));

	s->value = xstrdup(value);
	TAILQ_INSERT_TAIL(list, s, entries);
	return s;
}
