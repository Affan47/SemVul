dbgp_set_data(const void *buf, int size)
{
	const unsigned char *bytes = buf;
	u32 lo, hi;
	int i;

	lo = hi = 0;
	for (i = 0; i < 4 && i < size; i++)
		lo |= bytes[i] << (8*i);
	for (; i < 8 && i < size; i++)
		hi |= bytes[i] << (8*(i - 4));
	writel(lo, &ehci_debug->data03);
	writel(hi, &ehci_debug->data47);
}
