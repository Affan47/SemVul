data_cmp(const void *a, const void *b)
{
	int rcode;

	const CONF_DATA *one = a;
	const CONF_DATA *two = b;

	rcode = one->flag - two->flag;
	if (rcode != 0) return rcode;

	return strcmp(one->name, two->name);
}
