WaitTillCardIsFree(unsigned long base)
{
	unsigned int count = 0;
	unsigned int a = in_atomic();

	while (!(inw(base + 0xe) & 0x1) && count++ < 100)
		if (a)
			mdelay(1);
		else
			msleep(1);

	return !(inw(base + 0xe) & 0x1);
}
