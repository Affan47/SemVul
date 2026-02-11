arg_to_double(const char *arg)
{
	double d;
	if (sscanf(arg, "%lf", &d) != 1) {
		NORM_ERR("converting '%s' to double failed", arg);
		return 0.0;
	}
	return d;
}
