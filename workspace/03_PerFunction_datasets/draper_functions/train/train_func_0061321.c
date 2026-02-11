fz_store_scavenge(fz_context *ctx, unsigned int size, int *phase)
{
	fz_store *store;
	unsigned int max;

	if (ctx == NULL)
		return 0;
	store = ctx->store;
	if (store == NULL)
		return 0;

#ifdef DEBUG_SCAVENGING
	printf("Scavenging: store=%d size=%d phase=%d\n", store->size, size, *phase);
	fz_print_store(ctx, stderr);
	Memento_stats();
#endif
	do
	{
		unsigned int tofree;


		if (*phase >= 16)
			max = 0;
		else if (store->max != FZ_STORE_UNLIMITED)
			max = store->max / 16 * (16 - *phase);
		else
			max = store->size / (16 - *phase) * (15 - *phase);
		(*phase)++;


		if (size > UINT_MAX - store->size)
			tofree = UINT_MAX - max;
		else if (size + store->size > max)
			continue;
		else
			tofree = size + store->size - max;

		if (scavenge(ctx, tofree))
		{
#ifdef DEBUG_SCAVENGING
			printf("scavenged: store=%d\n", store->size);
			fz_print_store(ctx, stderr);
			Memento_stats();
#endif
			return 1;
		}
	}
	while (max > 0);

#ifdef DEBUG_SCAVENGING
	printf("scavenging failed\n");
	fz_print_store(ctx, stderr);
	Memento_listBlocks();
#endif
	return 0;
}
