rc_stringlist_addu(RC_STRINGLIST *list, const char *value)
{
	RC_STRING *s;

	TAILQ_FOREACH(s, list, entries)
	    if (strcmp(s->value, value) == 0) {
		    errno = EEXIST;
		    return NULL;
	    }

	return rc_stringlist_add(list, value);
}
