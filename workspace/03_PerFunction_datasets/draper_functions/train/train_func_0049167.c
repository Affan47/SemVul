init_accounts(void)
{
	myuser_heap = mowgli_heap_create(sizeof(myuser_t), HEAP_USER, BH_NOW);
	mynick_heap = mowgli_heap_create(sizeof(myuser_t), HEAP_USER, BH_NOW);
	myuser_name_heap = mowgli_heap_create(sizeof(myuser_name_t), HEAP_USER / 2, BH_NOW);
	mychan_heap = mowgli_heap_create(sizeof(mychan_t), HEAP_CHANNEL, BH_NOW);
	chanacs_heap = mowgli_heap_create(sizeof(chanacs_t), HEAP_CHANUSER, BH_NOW);
	mycertfp_heap = mowgli_heap_create(sizeof(mycertfp_t), HEAP_USER, BH_NOW);

	if (myuser_heap == NULL || mynick_heap == NULL || mychan_heap == NULL
			|| chanacs_heap == NULL || mycertfp_heap == NULL)
	{
		slog(LG_ERROR, "init_accounts(): block allocator failure.");
		exit(EXIT_FAILURE);
	}

	nicklist = mowgli_patricia_create(irccasecanon);
	oldnameslist = mowgli_patricia_create(irccasecanon);
	mclist = mowgli_patricia_create(irccasecanon);
	certfplist = mowgli_patricia_create(strcasecanon);
}
