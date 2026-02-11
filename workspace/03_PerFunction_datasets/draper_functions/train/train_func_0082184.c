ban_make(const ban_category_t cat,
	unsigned delay, unsigned requests, unsigned period,
	unsigned bantime, unsigned remind)
{
	struct ban *b;

	g_assert(period != 0);

	WALLOC0(b);

	b->magic = BAN_MAGIC;
	b->delay = delay;
	b->requests = requests;
	b->period = period;
	b->bantime = bantime;
	b->remind = remind;
	b->info = hevset_create_any(offsetof(struct addr_info, addr),
		host_addr_hash_func, host_addr_hash_func2, host_addr_eq_func);


	FORCE_ASSIGN(ban_category_t, b, cat, cat);
	FORCE_ASSIGN(float, b, decay_coeff, (float) requests / period);

	return b;
}
