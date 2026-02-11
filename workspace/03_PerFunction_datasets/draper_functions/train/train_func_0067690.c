removevar(var, pattern, plen, mode)
char **var;
CONST char *pattern;
int plen, mode;
{
	char *cp, **new;
	int i, n;

	n = countvar(var);
	new = (char **)Xmalloc((n + 1) * sizeof(char *));
	for (i = 0; i < n; i++) {
		if ((cp = removeword(var[i], pattern, plen, mode)))
			new[i] = cp;
		else new[i] = Xstrdup(var[i]);
	}
	new[i] = NULL;

	return(new);
}
