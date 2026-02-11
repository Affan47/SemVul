grow_string(struct lib_context *lc, char **string, const char *s)
{
	size_t len;
	char *tmp = *string;

	len = strlen(s) + (tmp ? strlen(tmp) + 1 : 1);
	if ((*string = dbg_realloc(tmp, len))) {
		if (!tmp)
			**string = '\0';
	}
	else if (tmp)
		dbg_free(tmp);

	return *string ? 1 : 0;
}
