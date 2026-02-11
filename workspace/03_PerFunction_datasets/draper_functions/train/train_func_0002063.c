limit_sysconf(int limit)
{
	long value;

	if ((value = sysconf(g.conf[limit].name)) == -1)
		return g.conf[limit].value;

	return value;
}
