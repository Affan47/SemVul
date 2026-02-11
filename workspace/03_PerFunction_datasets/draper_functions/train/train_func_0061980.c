arg_ep(char *arg)
{
	ULONG  v = strtoul(arg, (char **) 0, 0);
	SPQ.spq_end = v != 0? v - 1: MAXLONG-1;
}
