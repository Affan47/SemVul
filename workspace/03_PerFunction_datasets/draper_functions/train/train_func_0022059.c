keyname(const char *k)
{
	const char *p=strchr(k, ':');

	if (p)
		k=p+1;

	return k;
}
