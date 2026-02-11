mii_wbits(unsigned int ioaddr, unsigned data, int len)
{
    unsigned m = 1 << (len-1);
    for (; m; m >>= 1)
	mii_putbit(ioaddr, data & m);
}
