get_tablespace_io_concurrency(Oid spcid)
{
	TableSpaceCacheEntry *spc = get_tablespace(spcid);

	if (!spc->opts || spc->opts->effective_io_concurrency < 0)
		return effective_io_concurrency;
	else
		return spc->opts->effective_io_concurrency;
}
