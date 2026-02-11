sym_regtest(struct sym_hcb *np)
{
	register volatile u32 data;


	data = 0xffffffff;
	OUTL(np, nc_dstat, data);
	data = INL(np, nc_dstat);
#if 1
	if (data == 0xffffffff) {
#else
	if ((data & 0xe2f0fffd) != 0x02000080) {
#endif
		printf ("CACHE TEST FAILED: reg dstat-sstat2 readback %x.\n",
			(unsigned) data);
		return 0x10;
	}
	return 0;
}
