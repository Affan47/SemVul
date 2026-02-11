getstring(const char **ptr, char *buf, int buflen)
{
	const char *p;

	if (!ptr || !*ptr || !buf) return T_OP_INVALID;

	p = *ptr;

	while (*p && (isspace((int)*p))) p++;

	*ptr = p;

	if ((*p == '"') || (*p == '\'') || (*p == '`')) {
		return gettoken(ptr, buf, buflen);
	}

	return getthing(ptr, buf, buflen, 0, fr_tokens);
}
