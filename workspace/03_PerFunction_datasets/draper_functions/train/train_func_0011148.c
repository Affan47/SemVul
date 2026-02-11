compact_palloc0(IspellDict *Conf, size_t size)
{
	void	   *result;


	Assert(Conf->buildCxt != NULL);


	if (size > COMPACT_MAX_REQ)
		return palloc0(size);


	size = MAXALIGN(size);


	if (size > Conf->avail)
	{
		Conf->firstfree = palloc0(COMPACT_ALLOC_CHUNK);
		Conf->avail = COMPACT_ALLOC_CHUNK;
	}

	result = (void *) Conf->firstfree;
	Conf->firstfree += size;
	Conf->avail -= size;

	return result;
}
