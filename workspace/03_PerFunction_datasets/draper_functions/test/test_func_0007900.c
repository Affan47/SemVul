svis(char *mbdst, int c, int flags, int nextc, const char *mbextra)
{
	char cc[2];
	int ret;

	cc[0] = c;
	cc[1] = nextc;

	ret = istrsenvisx(mbdst, NULL, cc, 1, flags, mbextra, NULL);
	if (ret < 0)
		return NULL;
	return mbdst + ret;
}
