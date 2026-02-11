guc_malloc(int elevel, size_t size)
{
	void	   *data;

	data = malloc(size);
	if (data == NULL)
		ereport(elevel,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("out of memory")));
	return data;
}
