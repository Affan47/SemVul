dirmatch(char *s, char *t)
{
	size_t n;

	n = strlen(t);
	if (n == 0)
		return s;
	return !strncmp(s, t, n) && (s[n] == '/' || s[n] == 0 || s[n - 1] == '~') ? s + n : 0;
}
