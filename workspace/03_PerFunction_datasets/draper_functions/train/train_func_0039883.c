add_default_subtype(const char *progname, struct fuse_args *args)
{
	int res;
	char *subtype_opt;
	const char *basename = strrchr(progname, '/');
	if (basename == NULL)
		basename = progname;
	else if (basename[1] != '\0')
		basename++;

	subtype_opt = (char *) malloc(strlen(basename) + 64);
	if (subtype_opt == NULL) {
		fprintf(stderr, "fuse: memory allocation failed\n");
		return -1;
	}
	sprintf(subtype_opt, "-osubtype=%s", basename);
	res = fuse_opt_add_arg(args, subtype_opt);
	free(subtype_opt);
	return res;
}
