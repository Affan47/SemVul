regsub(unsigned char **z, int len, unsigned char *s)
{
	unsigned char **lst = NULL;
	int x;

	for (x = 0; x != len; ++x)
		if (rmatch(s, z[x]))
			lst = vaadd(lst, vsncpy(NULL, 0, sz(z[x])));
	return lst;
}
