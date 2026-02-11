calc_ev(uint32_t a0)
{
	uint32_t ev;

	ev = (a0 >> 24) & 0xf;
	if (ev == 0xf)
	{
		ev = 0x5;
	}
	ev *= 32;
	ev += (a0 & 0x1f);

	return ev;
}
