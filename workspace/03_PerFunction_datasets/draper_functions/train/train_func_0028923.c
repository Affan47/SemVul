_tw32_flush(struct tg3 *tp, u32 off, u32 val, u32 usec_wait)
{	DBGP("%s\n", __func__);

	tw32(off, val);
	if (usec_wait)
		udelay(usec_wait);
	tr32(off);


	if (usec_wait)
		udelay(usec_wait);
}
