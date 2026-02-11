random_collect(void (*cb)(void))
{
	static tm_t last;
	static time_delta_t prev;
	static time_delta_t running;
	static unsigned sum;
	tm_t now;
	time_delta_t d;
	unsigned r, m, a;
	uchar rbyte;

	tm_now_exact(&now);
	d = tm_elapsed_ms(&now, &last);
	m = tm2us(&now);


	a = (d & 0x3) ? UNSIGNED(d) : UNSIGNED((d >> 2) + d);
	a = (d & 0x17) ? a : UNSIGNED((d >> 4) + d);


	r = 0;

	if ((running & 0x3c) >= ((running - a) & 0x3c))
		r |= (1 << 0);

	if ((running & 0xf) >= (a & 0xf))
		r |= (1 << 1);

	if ((running & 0xf0) >= (a & 0xf0))
		r |= (1 << 2);

	if (((running + a) & 0xff) >= 0x80)
		r |= (1 << 3);

	r |= ((m / 127) & 0x78) << 1;

	if (prev == d)
		r = (r * 101) & 0xff;

	last = now;
	prev = d;
	running += a;


	sum += r;
	rbyte = sum & 0xff;

	random_pool_append(&rbyte, sizeof rbyte, cb);
}
