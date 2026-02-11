binvert(s)
char *s;
{
static char b[256];
int l = strlen(s) - 1, i = 0;

	while (l >= 0)
		b[i++] = s[l--];
	b[i] = '\0';
	return b;
}
