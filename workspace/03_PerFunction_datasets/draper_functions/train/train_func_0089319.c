skip_dash_dash(struct isl_arg *decl, const char *arg)
{
	if (!strncmp(arg, "--", 2))
		return arg + 2;
	if ((decl->flags & ISL_ARG_SINGLE_DASH) && arg[0] == '-')
		return arg + 1;
	return NULL;
}
