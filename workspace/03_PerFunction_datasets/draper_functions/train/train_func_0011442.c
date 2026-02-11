atooctal(s)
CONST char *s;
{
	int n;

	if (!Xsscanf(s, "%<o%$", &n)) return(-1);
	n &= 0777;

	return(n);
}
