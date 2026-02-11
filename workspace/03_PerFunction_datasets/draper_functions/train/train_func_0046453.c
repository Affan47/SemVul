is_assignment(const char *expr)
{
	char *exprc, *val, *s, *s1;

	if (!isalnum_(*expr) || (val = strchr(expr, '=')) == NULL) {
		return FALSE;
	}

	exprc = xstrdup(expr);
	val = exprc + (val - expr);
	*val++ = '\0';

	s = s1 = val;
	while ((*s1 = nextchar(&s)) != '\0')
		s1++;

	setvar_u(newvar(exprc), val);
	free(exprc);
	return TRUE;
}
