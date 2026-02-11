cusexmp_process_arg(void *data, const char *arg, int key,
			       struct fuse_args *outargs)
{
	struct cusexmp_param *param = data;

	(void)outargs;
	(void)arg;

	switch (key) {
	case 0:
		param->is_help = 1;
		fprintf(stderr, "%s", usage);
		return fuse_opt_add_arg(outargs, "-ho");
	default:
		return 1;
	}
}
