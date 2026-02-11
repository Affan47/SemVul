ParsePlugin_counter (const char *p, size_t length, void *vp)
{
	if (!p || !vp || length < 0)
	{
		err("authpgsql: bad arguments while counting "
				 "query string");
		return -1;
	}

	*((size_t *)vp) += length;

	return 0;
}
