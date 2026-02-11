lstrndup(char *str, int n)
{
	char *r;
	r = malloc(n+1);
	if (r) {
		strncpy(r, str, n);
		r[n] = 0;
	}
	return r;
}
