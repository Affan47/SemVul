expandvar(var, ident, len)
char **var;
CONST char *ident;
int len;
{
	int i;

	if (searchvar(var, ident, len, '\0') >= 0) return(var);
	i = countvar(var);
	var = (char **)Xrealloc(var, (i + 2) * sizeof(char *));
	var[i] = Xstrndup(ident, len);
	var[++i] = NULL;

	return(var);
}
