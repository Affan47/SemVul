uuid_gen(uuid *u)
{
	static uint64_t s_last = 0;
	static uint64_t s_cnt = 0;

	if (!s_seed)
		uuid_seed(time(0));

	struct timeval tp;
	gettimeofday(&tp, 0);
	uint64_t now = tp.tv_sec;
	now *= 1000L * 1000L;
	now += tp.tv_usec;

	if (now != s_last)
	{
		s_last = now;
		s_cnt = 1;
	}

	u->u1 = now;
	u->u2 = s_cnt++ << BITS_48;
	u->u2 |= s_seed;
	return u;
}
