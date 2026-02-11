get_path_from_symbol(const char *symbol, const char **p, size_t *len)
{
    if (symbol[0] == '0') {

	*p   = strchr(symbol, '/');
	if (*p == NULL) return 0;
	*len = strlen(*p);
    }
    else {

	const char *q;
	*p   = symbol;
	q   = strchr(symbol, '(');
	if (q == NULL) return 0;
	*len = q - symbol;
    }
    return 1;
}
