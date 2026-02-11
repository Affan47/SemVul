mchip_delay(u32 reg, u32 v)
{
	int n = 10;
	while (--n && mchip_read(reg) != v)
		udelay(1);
	return n;
}
