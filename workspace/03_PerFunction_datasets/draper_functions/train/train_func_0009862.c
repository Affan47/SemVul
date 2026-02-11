qual_desc(s, opt, not)
	char *s;
	const struct qual_options *opt;
	int not;
{
	if (isdigit((unsigned char)*s)) {
		int desc = atoi(s);
		if (desc < 0 || desc >= MAX_QUALS)
			return -1;
		qualify_one(desc, opt, not, -1);
		return 0;
	}
	return -1;
}
