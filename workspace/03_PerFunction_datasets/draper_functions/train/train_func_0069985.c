recolor(byte *buf, byte fill, int cnt)
{
	while (cnt--) *(buf++) |= fill;
}
