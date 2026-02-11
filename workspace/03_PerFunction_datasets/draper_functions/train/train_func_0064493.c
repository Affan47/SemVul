geteol(s)
CONST char *s;
{
	int i;

	for (i = 0; s[i]; i++) {
		if (s[i] == '\\') {
			if (!s[++i]) return(-1);
		}
		else if (iskanji1(s, i)) i++;
		else if (s[i] == '"') break;
	}
	if (!s[i]) return(-1);

	return(i);
}
