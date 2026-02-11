rmon_update(struct cmac *mac, unsigned int addr, u64 *stat)
{
	u32 v, lo;

	vsc_read(mac->adapter, addr, &v);
	lo = *stat;
	*stat = *stat - lo + v;

	if (v == 0)
		return;

	if (v < lo)
		*stat += (1ULL << 32);
}
