sios_param_set_invbool(const char *val, struct sios_param *p)
{
	int boolval, ret;
	struct sios_param dummy = { .arg = &boolval };

	ret = sios_param_set_bool(val, &dummy);
	if (ret == 0)
		*(int *)p->arg = !boolval;
	return ret;
}
