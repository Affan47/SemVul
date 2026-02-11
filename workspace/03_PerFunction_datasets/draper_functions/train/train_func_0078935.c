skipquote(s, ptrp)
CONST char *s;
int *ptrp;
{
	static int q = '\0';
	int pc;

	if (!*ptrp) q = '\0';
	pc = parsechar(&(s[*ptrp]), -1, '\0', 0, &q, NULL);
	if (pc == PC_NORMAL) return(0);
	if (pc == PC_WCHAR || pc == PC_ESCAPE) {
		(*ptrp)++;
		return(2);
	}

	return(1);
}
