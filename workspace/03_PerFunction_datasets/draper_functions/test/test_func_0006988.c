config_smallint(struct configuration *p, int *i)
{
	const char *t;
	unsigned long u;

	t = config_int(p, &u);
	if (t)
		return t;
	if (u > CONF_SMALLINT_MAX)
		return e_toobig;
	*i = u;
	return 0;
}
