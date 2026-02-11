set_default_bool(struct isl_arg *arg, void *opt)
{
	if (arg->offset == (size_t) -1)
		return;
	*(unsigned *)(((char *)opt) + arg->offset) = arg->u.b.default_value;
}
