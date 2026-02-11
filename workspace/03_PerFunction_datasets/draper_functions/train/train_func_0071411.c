print_gid(const char *val, unsigned int base)
{
	int gid;
	char name[64];

	errno = 0;
	gid = strtoul(val, NULL, base);
	if (errno) {
		printf("conversion error(%s) ", val);
		return;
	}

	printf("%s ", aulookup_gid(gid, name, sizeof(name)));
}
