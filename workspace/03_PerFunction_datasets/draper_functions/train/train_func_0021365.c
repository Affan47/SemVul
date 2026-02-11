parse_size( conffile_t *cfile )
{
	char *p;
	int ret;

	ret = strtol (cfile->val, &p, 10);
	if (*p == 'k' || *p == 'K')
		ret *= 1024, p++;
	else if (*p == 'm' || *p == 'M')
		ret *= 1024 * 1024, p++;
	if (*p == 'b' || *p == 'B')
		p++;
	if (*p) {
		fprintf (stderr, "%s:%d: invalid size '%s'\n",
		         cfile->file, cfile->line, cfile->val);
		cfile->err = 1;
		return 0;
	}
	return ret;
}
