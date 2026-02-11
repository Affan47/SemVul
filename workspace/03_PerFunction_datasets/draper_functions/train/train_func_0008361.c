from6(unsigned char c)
{
	char *p;

	c = ebc2asc0[c];
	p = strchr(table6, c);
	if (p == CN)
		return 0;
	return p - table6;
}
