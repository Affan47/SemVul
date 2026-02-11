ComputeIoConcurrency(int io_concurrency, double *target)
{
	double		new_prefetch_pages = 0.0;
	int			i;


	io_concurrency = Min(Max(io_concurrency, 0), MAX_IO_CONCURRENCY);


	for (i = 1; i <= io_concurrency; i++)
		new_prefetch_pages += (double) io_concurrency / (double) i;

	*target = new_prefetch_pages;


	return (new_prefetch_pages > 0.0 && new_prefetch_pages < (double) INT_MAX);
}
