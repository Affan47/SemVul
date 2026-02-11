next_arg(struct isl_arg *arg, int a)
{
	for (++a; arg[a].type != isl_arg_end; ++a)
		if (arg[a].type == isl_arg_arg)
			return a;

	return -1;
}
